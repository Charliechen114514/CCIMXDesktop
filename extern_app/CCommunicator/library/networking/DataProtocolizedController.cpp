#include "DataProtocolizedController.h"
#include "DataSinker.h"
#include "ISinkerRouter.h"
#include <QDir>
#include <QElapsedTimer>
#include <QSaveFile>
namespace {
static constexpr quint32 MAX_NAME_LEN = 64 * 1024; // 64 KiB
static constexpr quint32 MAX_PAYLOAD_SIZE = 10 * 1024 * 1024; // 10 MiB
static constexpr quint64 MAX_TOTAL_SIZE = (1ULL << 40); //
}

DataProtocolizedController::~DataProtocolizedController() {
    if (elapsed_timeout) {
        delete elapsed_timeout; // Clean up the elapsed timer
    }
}

DataProtocolizedController::DataProtocolizedController(
    QObject* parent, ISinkerRouter* sinker)
    : QObject(parent)
    , router(sinker)
    , state(DataHeaderUtils::CurrentState::ReadingHeader) {
    if (!sinker) {
        throw std::invalid_argument("Sinker can not be null!");
    }
    elapsed_timeout = new QElapsedTimer();
}

void DataProtocolizedController::sendData(DataSinker* send_sinker,
                                          int chunkSize, qint64 startOffset) {
    this->send_sinker = send_sinker;
    const auto fileID
        = send_sinker->id_generator();
    sendFileSize = send_sinker->size();

    sendStartFrame(fileID, send_sinker->provide_name(), sendFileSize);

    if (startOffset < 0 || startOffset > sendFileSize)
        startOffset = 0;
    sendFileHasSent = startOffset;

    while (sendFileHasSent < sendFileSize) {
        const qint64 bytesToRead = qMin(static_cast<qint64>(chunkSize),
                                        static_cast<qint64>(sendFileSize - sendFileHasSent));
        QByteArray chunk = send_sinker->requestChunkForEncoding(sendFileHasSent, bytesToRead);
        const quint64 offset
            = sendFileHasSent;
        sendDataFrame(fileID, offset, chunk, sendFileSize);
        sendFileHasSent += chunk.size();
        emit sendProgress(sendFileHasSent, sendFileSize);
    }

    sendEndFrame(fileID, sendFileSize);
    // qDebug() << "Ok Send Finished! will run sendEnd";
    send_sinker->sendEnd();
}

void DataProtocolizedController::sendStartFrame(quint64 fileId, const QString& name, quint64 totalSize) {

    QByteArray _name = name.toUtf8();

    DataHeaderUtils::DataHeader h {};
    h.header_magic = DataHeaderUtils::HEADER_MAGIC;
    h.protocol_version = DataHeaderUtils::HEADER_VERSION;
    h.current_state = static_cast<quint8>(DataHeaderUtils::OperationState::Start);
    h.payload_type = static_cast<quint8>(send_sinker->sinkerType());
    h.fileId = fileId;
    h.offset = 0;
    h.totalSize = totalSize;
    h.nameLen = static_cast<quint32>(_name.size());
    h.payloadSize = 0;
    QByteArray frame = DataHeaderUtils::packUpHeader(h);
    frame.append(_name);
    // qDebug() << "Packup the start frame OK ";
    // DataHeaderUtils::printDataHeader(h);
    emit frameReady(frame);
}

void DataProtocolizedController::sendDataFrame(quint64 fileId, quint64 offset, const QByteArray& chunk, quint64 totalSize) {

    DataHeaderUtils::DataHeader h {};
    h.header_magic = DataHeaderUtils::HEADER_MAGIC;
    h.protocol_version = DataHeaderUtils::HEADER_VERSION;
    h.current_state = static_cast<quint8>(DataHeaderUtils::OperationState::Data);
    h.payload_type = static_cast<quint8>(send_sinker->sinkerType());
    h.fileId = fileId;
    h.offset = offset;
    h.totalSize = totalSize;
    h.nameLen = 0;
    h.payloadSize = static_cast<quint32>(chunk.size());

    QByteArray frame = DataHeaderUtils::packUpHeader(h);
    // qDebug() << "Packup the data frame OK ";
    // DataHeaderUtils::printDataHeader(h);
    frame.append(chunk);
    emit frameReady(frame);
}

void DataProtocolizedController::sendEndFrame(quint64 fileId, quint64 totalSize) {

    DataHeaderUtils::DataHeader h {};
    h.header_magic = DataHeaderUtils::HEADER_MAGIC;
    h.protocol_version = DataHeaderUtils::HEADER_VERSION;
    h.current_state = static_cast<quint8>(DataHeaderUtils::OperationState::End);
    h.payload_type = static_cast<quint8>(send_sinker->sinkerType());
    h.fileId = fileId;
    h.offset = totalSize;
    h.totalSize = totalSize;
    h.nameLen = 0;
    h.payloadSize = 0;

    QByteArray frame = DataHeaderUtils::packUpHeader(h);
    // qDebug() << "Packup the end frame OK ";
    // DataHeaderUtils::printDataHeader(h);
    emit frameReady(frame);
}

void DataProtocolizedController::onBytes(const QByteArray& bytes) {
    // qDebug() << "Bytes comes! " << bytes;
    rx_buffer.append(bytes);
    parse();
}

void DataProtocolizedController::parse() {
    if (!elapsed_timeout->isValid()) {
        elapsed_timeout->start();
    }

    bool advanced = true;
    while (advanced) {
        if (elapsed_timeout->isValid() && elapsed_timeout->elapsed() > PARSE_TIMEOUT_MS) {
            // qDebug() << "Elapsed Timer: " << elapsed_timeout->elapsed()
            // << "but the PARSE_TIMEOUT_MS" << PARSE_TIMEOUT_MS;
            emit parsingBad();
            // qDebug() << "Parsing bad!";
            rx_buffer.clear();
            elapsed_timeout->restart(); // 超时后重新计时
            state = DataHeaderUtils::CurrentState::ReadingHeader;
            return;
        }

        switch (state) {
        case DataHeaderUtils::CurrentState::ReadingHeader: {
            // OK, this is the start session
            advanced = parseHeader();
            // qDebug() << "parseHeader OK";
        } break;
        case DataHeaderUtils::CurrentState::ReadingName:
            advanced = parseName();
            break;
        case DataHeaderUtils::CurrentState::ReadingPayload:
            advanced = parseData();
            break;
        }

        // qDebug() << "Timer reset!";
        if (elapsed_timeout->isValid())
            elapsed_timeout->restart();
    }
}
bool DataProtocolizedController::parseHeader() {
    if (rx_buffer.size() < static_cast<int>(DataHeaderUtils::DATAHEADER_SIZE))
        return false;
    DataHeaderUtils::DataHeader h {};
    QByteArray headerBytes = rx_buffer.left(static_cast<int>(DataHeaderUtils::DATAHEADER_SIZE));

    QDataStream ds(headerBytes);
    ds.setByteOrder(QDataStream::BigEndian);
    // qDebug() << "Attempt read headers";
    if (!DataHeaderUtils::readOutHeader(ds, h)) {
        emit protocolError(QStringLiteral("Header corrupt or CRC mismatch, discarding 1 byte"));
        rx_buffer.remove(0, 1);
        return true; // 继续 while-loop，再试
    }

    // 基于整型直接判断 magic 与 version
    // qDebug() << "Attempt magic and versions";
    if (h.header_magic != DataHeaderUtils::HEADER_MAGIC) {
        emit protocolError(QStringLiteral("Magic mismatch, discarding 1 byte"));
        rx_buffer.remove(0, 1);
        return true;
    }
    if (h.protocol_version != DataHeaderUtils::HEADER_VERSION) {
        emit protocolError(QStringLiteral("Unsupported protocol version"));
        // 版本不兼容，直接清空缓存，等待上层重新同步（或断开）
        rx_buffer.clear();
        return false;
    }

    // 限制防护
    if (h.nameLen > MAX_NAME_LEN || h.payloadSize > MAX_PAYLOAD_SIZE || h.totalSize > MAX_TOTAL_SIZE) {
        emit protocolError(QStringLiteral("Header fields too large, clearing buffer"));
        rx_buffer.clear();
        return false;
    }

    // 头部无误：移除缓存中的 header
    // qDebug() << "Header OK";
    rx_buffer.remove(0, static_cast<int>(DataHeaderUtils::DATAHEADER_SIZE));
    internal_header = h;
    curFileIdStr = QString::number(h.fileId);
    DataHeaderUtils::PayloadType payload_type = static_cast<DataHeaderUtils::PayloadType>(h.payload_type);
    // qDebug() << "Get the Payload Type" << h.payload_type;
    if (!receive_sinker || // if null
        receive_sinker->sinkerType() != payload_type) {
        receive_sinker = router->createSinkerForReceive(payload_type);
    }

    const auto opState = static_cast<DataHeaderUtils::OperationState>(h.current_state);
    switch (opState) {
    case DataHeaderUtils::OperationState::Start:
        if (h.nameLen == 0) {
            emit protocolError(QStringLiteral("Start frame with zero nameLen"));
            rx_buffer.clear();
            return false;
        }
        curReceived = 0;
        state = DataHeaderUtils::CurrentState::ReadingName;
        break;
    case DataHeaderUtils::OperationState::Data:
        state = DataHeaderUtils::CurrentState::ReadingPayload;
        break;
    case DataHeaderUtils::OperationState::End: {
        if (!receive_sinker->receiveEnd()) {
            emit protocolError(QStringLiteral("sinker's receiveEnd() failed"));
        }
        elapsed_timeout->invalidate();
        // qDebug() << "Prepare to send Buffer OK";
        emit bufferOk(receive_sinker);
        state = DataHeaderUtils::CurrentState::ReadingHeader;
        return false; // OK we shell quit
    }
    default:
        emit protocolError(QStringLiteral("Unknown operation state"));
        rx_buffer.clear();
        return false;
    }

    return true;
}

bool DataProtocolizedController::parseName() {
    const int need = static_cast<int>(internal_header.nameLen);
    if (!ensureSize(need))
        return false;

    const QByteArray nameBytes = rx_buffer.left(need);
    rx_buffer.remove(0, need);

    if (!receive_sinker) {
        qCritical() << "Error in Receive Sinker As NULL";
        return false;
    }

    receive_sinker->consume_name(QString::fromUtf8(nameBytes));
    state = DataHeaderUtils::CurrentState::ReadingHeader;
    return true;
}

bool DataProtocolizedController::parseData() {
    const int need = static_cast<int>(internal_header.payloadSize);
    if (!ensureSize(need))
        return false;

    const QByteArray payload = rx_buffer.left(need);
    rx_buffer.remove(0, need);

    if (!receive_sinker) {
        qCritical() << "Error in Receive Sinker As NULL";
        return false;
    }

    if (!receive_sinker->consumeChunkBuffer(payload)) {
        emit protocolError(QStringLiteral("consumeChunkBuffer error"));
    } else {
        curReceived += static_cast<quint64>(payload.size());
        emit receiveProgress(curFileIdStr, curReceived, internal_header.totalSize);
    }

    // Data 一帧解析完，回到读下一帧 header
    state = DataHeaderUtils::CurrentState::ReadingHeader;
    return true;
}

void DataProtocolizedController::reset() {
    rx_buffer.clear();
    state = DataHeaderUtils::CurrentState::ReadingHeader;
    curFileIdStr.clear();
    curReceived = 0;
    internal_header = DataHeaderUtils::DataHeader();
    sendFileSize = 0;
    sendFileHasSent = 0;

    if (elapsed_timeout) {
        elapsed_timeout->invalidate(); // 相当于停止计时
    }

    emit protocolError(QStringLiteral("Controller has been reset."));
}

bool DataProtocolizedController::ensureSize(int need) const {
    return rx_buffer.size() >= need;
}
