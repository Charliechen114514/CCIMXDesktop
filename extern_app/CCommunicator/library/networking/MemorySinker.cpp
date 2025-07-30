#include "MemorySinker.h"
#include "DataHeader.h"
#include <QDebug>

MemorySinker::MemorySinker(const QString& name)
    : DataSinker(DataHeaderUtils::PayloadType::Text)
    , name_(name) { }

MemorySinker::~MemorySinker() = default;

QString MemorySinker::provide_name() {
    return name_;
}

void MemorySinker::consume_name(const QString& name) {
    name_ = name;
}

qint64 MemorySinker::id_generator() {
    return DataHeaderUtils::fileId_generation();
}

quint64 MemorySinker::size() {
    return static_cast<quint64>(buffer_.size());
}

bool MemorySinker::consumeChunkBuffer(const QByteArray& chunk) {
    buffer_.append(chunk);
    return true;
}

QByteArray MemorySinker::requestChunkForEncoding(quint64 offset, quint64 bytesForRead) {
    if (offset >= static_cast<quint64>(buffer_.size()))
        return {};
    auto len = qMin(bytesForRead, static_cast<quint64>(buffer_.size()) - offset);
    return buffer_.mid(static_cast<int>(offset), static_cast<int>(len));
}

bool MemorySinker::receiveEnd() {
    qDebug() << "[MemorySinker] Receive end. Total size:" << buffer_.size();
    emit accept_data_receive();
    return true;
}

void MemorySinker::sendEnd() {
    buffer_.clear();
}

void MemorySinker::initMemoryBuffer(const QByteArray& chunk) {
    buffer_.append(chunk);
}

void MemorySinker::resetSelf() {
    buffer_.clear();
}
