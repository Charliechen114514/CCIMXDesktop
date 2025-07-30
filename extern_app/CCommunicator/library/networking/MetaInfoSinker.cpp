#include "MetaInfoSinker.h"
#include "DataHeader.h"
#include <QDebug>
MetaInfoSinker::MetaInfoSinker(QObject* parent)
    : DataSinker { DataHeaderUtils::PayloadType::UnPublicMeta } {
}

MetaInfoSinker::~MetaInfoSinker() = default;

QString MetaInfoSinker::provide_name() {
    return name_;
}

void MetaInfoSinker::consume_name(const QString& name) {
    name_ = name;
}

qint64 MetaInfoSinker::id_generator() {
    return DataHeaderUtils::fileId_generation();
}

quint64 MetaInfoSinker::size() {
    return static_cast<quint64>(buffer_.size());
}

bool MetaInfoSinker::consumeChunkBuffer(const QByteArray& chunk) {
    buffer_.append(chunk);
    return true;
}

QByteArray MetaInfoSinker::requestChunkForEncoding(quint64 offset, quint64 bytesForRead) {
    if (offset >= static_cast<quint64>(buffer_.size()))
        return {};
    auto len = qMin(bytesForRead, static_cast<quint64>(buffer_.size()) - offset);
    return buffer_.mid(static_cast<int>(offset), static_cast<int>(len));
}

bool MetaInfoSinker::receiveEnd() {
    qDebug() << "[MetaInfoSinker] Receive end. Total size:" << buffer_.size();
    emit accept_data_receive();
    return true;
}

void MetaInfoSinker::sendEnd() {
    buffer_.clear();
}

void MetaInfoSinker::initMemoryBuffer(const QByteArray& chunk) {
    buffer_.append(chunk);
}

void MetaInfoSinker::resetSelf() {
    buffer_.clear();
}
