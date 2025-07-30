#include "Session.h"
#include "DataHeader.h"
#include "DataProtocolizedController.h"
#include "DataSinker.h"
#include "FileSinker.h"
#include "ISinkerRouter.h"
#include "PeerConnection.h"
#include "SessionError.h"
#include "SessionInfo.h"
#include <QBuffer>
#include <QDataStream>
#include <QDebug>
#include <QImage>
static constexpr int HEADER_MIN_SIZE = sizeof(DataHeaderUtils::DataHeader);

// ============================================================================
// ctor / dtor
// ============================================================================
Session::Session(PeerConnection* transport,
                 const SessionInfo& localName,
                 QObject* parent)
    : QObject(parent)
    , transport(transport)
    , localInfo(localName)
    , controller(new DataProtocolizedController) {
    Q_ASSERT(transport);

    connect(transport, &PeerConnection::connected,
            this, &Session::onConnected);
    connect(transport, &PeerConnection::disconnected,
            this, &Session::onDisconnected);
    connect(transport, &PeerConnection::errorOccurred,
            this, [this](const QAbstractSocket::SocketError e) {
                QString errorString;
                int code;
                SessionError::transfer(e, errorString, code);
                emit error(this, errorString, code);
            });
    connect(transport, &PeerConnection::dataReceived,
            controller, &DataProtocolizedController::onBytes);
    connect(controller, &DataProtocolizedController::frameReady,
            transport, &PeerConnection::send_data);
    connect(controller, &DataProtocolizedController::bufferOk,
            this, &Session::sinkerOk);
}

int Session::port_running() const {
    return transport->selfInfo().port;
}

std::pair<QString, int> Session::peerInfo() const {
    return { transport->peerInfo().host_address, transport->peerInfo().target_port };
}

Session::~Session() = default;

void Session::sendText(const QString& text) {
    auto sinker = controller->get_router()->createSinkerForSend(DataHeaderUtils::PayloadType::Text);
    sinker->initMemoryBuffer(text.toUtf8());
    controller->sendData(sinker);
}

void Session::sendImage(const QImage& image) {
    auto sinker = controller->get_router()->createSinkerForSend(DataHeaderUtils::PayloadType::Image);
    QByteArray imageBytes;
    QBuffer buf(&imageBytes);
    buf.open(QIODevice::WriteOnly);
    image.save(&buf, "PNG");
    sinker->initMemoryBuffer(imageBytes);
    controller->sendData(sinker);
}

void Session::sendFile(const QString& filePath) {
    auto sinker = controller->get_router()->createSinkerForSend(DataHeaderUtils::PayloadType::Image);
    auto fileSinker = dynamic_cast<FileSinker*>(sinker);
    fileSinker->setFilePath(filePath);
    controller->sendData(sinker);
}

QString Session::sessionID() const {
    return transport->uuid();
}

void Session::onConnected() {
    emit connected(this);
    // OK, we should shake hands for exchange the session info
    qDebug() << "Session is invoked onConnected";
    shake_hands_to_peers();
}

void Session::onDisconnected() {
    communicate_ready = false;
    emit disconnected(this);
}

#include "FileSinker.h"
#include "ImageSinker.h"
#include "MemorySinker.h"
#include "MetaInfoSinker.h"
void Session::sinkerOk(DataSinker* sinker) {
    switch (sinker->sinkerType()) {
    case DataHeaderUtils::PayloadType::Text: {
        MemorySinker* textSinker = dynamic_cast<MemorySinker*>(sinker);
        emit textReceived(textSinker->getBuffer());
    } break;
    case DataHeaderUtils::PayloadType::Image: {
        ImageSinker* imageSinker = dynamic_cast<ImageSinker*>(sinker);
        emit imageReceived(imageSinker->getImage());
    } break;
    case DataHeaderUtils::PayloadType::File: {
        FileSinker* fileSinker = dynamic_cast<FileSinker*>(sinker);
        emit fileReceived(fileSinker->filePathSave());
    } break;
    case DataHeaderUtils::PayloadType::UnPublicMeta:
        if (!communicate_ready) {
            // OK, we need to parse Datas;
            MetaInfoSinker* metaInfo = dynamic_cast<MetaInfoSinker*>(sinker);
            attempt_parse_hello(metaInfo->metaRaw());
            communicate_ready = true;
        } else {
            qCritical() << "Unwelcome UnPublicMeta transmitions!";
        }
        break;
    }

    sinker->resetSelf();
}

void Session::shake_hands_to_peers() {
    qDebug() << "Shake hands";
    auto sinker = controller->get_router()->createSinkerForSend(
        DataHeaderUtils::PayloadType::UnPublicMeta);
    sinker->initMemoryBuffer(localInfo.toProtocalString());
    controller->sendData(sinker);
}

void Session::attempt_parse_hello(const QByteArray& e) {
    try {
        remoteInfo = SessionInfo(e);
    } catch (const std::exception& e) {
        qCritical() << "Unsuccess meta created!";
    }
    qDebug() << "Parse OK, peer nickname: " << remoteInfo.nickName;
    emit ready(this, remoteInfo);
}
