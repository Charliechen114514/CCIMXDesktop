#pragma once

#include "DataSinker.h"
#include <QByteArray>
#include <QObject>
#include <QString>

class MemorySinker : public DataSinker {
public:
    explicit MemorySinker(const QString& name = "memory_data");
    ~MemorySinker() override;

    QString provide_name() override;
    void consume_name(const QString& name) override;
    qint64 id_generator() override;
    QByteArray requestChunkForEncoding(quint64 offset, quint64 bytesForRead) override;
    quint64 size() override;
    bool receiveEnd() override;
    bool consumeChunkBuffer(const QByteArray& chunk) override;
    void sendEnd() override;
    void initMemoryBuffer(const QByteArray& chunk) override;
    QByteArray getBuffer() {
        return buffer_;
    };

    void resetSelf() override;

private:
    QString name_;
    QByteArray buffer_;
};
