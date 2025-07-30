#pragma once
#include "DataHeader.h"
#include "DataSinker.h"
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QSaveFile>
#include <QString>

class FileSinker : public DataSinker {
public:
    explicit FileSinker(const QString& filePath, int chunkSize = 4096);
    void setFilePath(const QString& filePath);
    QString filePathSave() const { return filePath_; }
    QString provide_name() override;
    quint64 size() override;
    qint64 id_generator() override;
    bool receiveEnd() override;
    void consume_name(const QString& name) override;
    bool consumeChunkBuffer(const QByteArray& chunk) override;
    void initMemoryBuffer(const QByteArray& chunk) override { }
    QByteArray requestChunkForEncoding(
        quint64 offset, quint64 bytesForRead) override;
    void sendEnd() override;
    void resetSelf() override;

private:
    int send_offset_;
    QString filePath_;
    int chunkSize_;
    QFile file_;
    QScopedPointer<QSaveFile> saveFile_;
};
