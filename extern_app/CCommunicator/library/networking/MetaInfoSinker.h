#ifndef METAINFOSINKER_H
#define METAINFOSINKER_H
#include "DataSinker.h"

class MetaInfoSinker : public DataSinker {
public:
    explicit MetaInfoSinker(QObject* parent = nullptr);
    ~MetaInfoSinker();
    QString provide_name() override;
    void consume_name(const QString& name) override;
    qint64 id_generator() override;
    QByteArray requestChunkForEncoding(quint64 offset, quint64 bytesForRead) override;
    quint64 size() override;
    bool receiveEnd() override;
    bool consumeChunkBuffer(const QByteArray& chunk) override;
    void sendEnd() override;
    void initMemoryBuffer(const QByteArray& chunk) override;
    QByteArray metaRaw() const {
        return buffer_;
    };

    void resetSelf() override;

protected:
    QString name_ { "metaInfo" };
    QByteArray buffer_;
};

#endif // METAINFOSINKER_H
