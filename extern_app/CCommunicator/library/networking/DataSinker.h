#pragma once

#include "DataHeader.h"
#include <QByteArray>
#include <QObject>
#include <QString>
class DataProtocolizedController;
class DataSinker : public QObject {
    friend class DataProtocolizedController;
    Q_OBJECT
public:
    DataSinker(DataHeaderUtils::PayloadType t, QObject* parent = nullptr)
        : QObject(parent)
        , type(t) {
    }
    virtual ~DataSinker() = default;
    virtual QString provide_name() = 0;
    virtual void consume_name(const QString& name) = 0;
    virtual qint64 id_generator() = 0;
    virtual QByteArray requestChunkForEncoding(quint64 offset, quint64 bytesForRead) = 0;
    virtual quint64 size() = 0;
    virtual bool receiveEnd() = 0;
    virtual bool consumeChunkBuffer(const QByteArray& chunk) = 0;
    virtual void initMemoryBuffer(const QByteArray& chunk) = 0;
    virtual void sendEnd() = 0;
    virtual void resetSelf() = 0;

    DataHeaderUtils::PayloadType sinkerType() const {
        return type;
    }
signals:
    void accept_data_receive();

private:
    DataHeaderUtils::PayloadType type;
};
