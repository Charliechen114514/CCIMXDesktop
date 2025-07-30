#include "ImageSinker.h"
#include "DataHeader.h"
#include <QDebug>
#include <QDir>
#include <QFileInfo>

ImageSinker::ImageSinker(const QString& baseSavePath)
    : DataSinker(DataHeaderUtils::PayloadType::Image)
    , baseSavePath_(baseSavePath) { }

ImageSinker::~ImageSinker() {
    ImageSinker::sendEnd();
}

QString ImageSinker::provide_name() {
    // 可返回固定名字或基于时间戳随机名
    return QFileInfo(saveFilePath_).fileName();
}

void ImageSinker::consume_name(const QString& name) {
    // 拼出完整保存路径，增加 _received 标记
    QString baseName = QFileInfo(name).baseName();
    QString suffix = QFileInfo(name).suffix();
    QString newName = baseName + "_received." + suffix;
    saveFilePath_ = QDir(baseSavePath_).filePath(newName);

    saveFile_.setFileName(saveFilePath_);
    if (!saveFile_.open(QIODevice::WriteOnly)) {
        qCritical() << "[ImageSinker] Cannot open save file:" << saveFilePath_
                    << ", error:" << saveFile_.errorString();
    } else {
        qDebug() << "[ImageSinker] Ready to receive image file:" << saveFilePath_;
        isReceiving_ = true;
        buffer_.clear();
    }
}

qint64 ImageSinker::id_generator() {
    return DataHeaderUtils::fileId_generation();
}

quint64 ImageSinker::size() {
    return static_cast<quint64>(buffer_.size());
}

bool ImageSinker::consumeChunkBuffer(const QByteArray& chunk) {
    if (!isReceiving_) {
        qCritical() << "[ImageSinker] Not ready to receive data chunk.";
        return false;
    }

    // 先写入文件
    qint64 written = saveFile_.write(chunk);
    if (written != chunk.size()) {
        qCritical() << "[ImageSinker] Write chunk size mismatch";
        return false;
    }

    // 同时累积到 buffer，方便后续 QImage 解析
    buffer_.append(chunk);
    return true;
}

QByteArray ImageSinker::requestChunkForEncoding(quint64 offset, quint64 bytesForRead) {
    if (offset >= static_cast<quint64>(buffer_.size()))
        return QByteArray(); // 无效读取
    return buffer_.mid(static_cast<int>(offset), static_cast<int>(bytesForRead));
}

bool ImageSinker::receiveEnd() {
    if (saveFile_.isOpen()) {
        if (!saveFile_.commit()) {
            qWarning() << "[ImageSinker] commit() failed:" << saveFile_.errorString();
            saveFile_.cancelWriting();
        }
    }

    isReceiving_ = false;

    // 使用累积的 buffer 尝试解析图像
    if (!buffer_.isEmpty()) {
        if (!image_.loadFromData(buffer_)) {
            qWarning() << "[ImageSinker] Failed to load image from data";
            return false;
        } else {
            qDebug() << "[ImageSinker] Image loaded successfully";
            emit accept_data_receive();
        }
    }
    return true;
}

void ImageSinker::sendEnd() {
    if (saveFile_.isOpen()) {
        if (!saveFile_.commit()) {
            qWarning() << "[ImageSinker] commit() failed:" << saveFile_.errorString();
            saveFile_.cancelWriting();
        }
    }
    isReceiving_ = false;
}

void ImageSinker::initMemoryBuffer(const QByteArray& chunk) {
    buffer_ = chunk;
    fileSize_ = buffer_.size();
    isReceiving_ = false; // 表示当前是发送状态
}

QImage ImageSinker::getImage() const {
    return image_;
}

void ImageSinker::resetSelf() {
    buffer_.clear();
    baseSavePath_ = "";
    fileSize_ = 0;
    isReceiving_ = false;
}
