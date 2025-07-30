#ifndef IMAGESINKER_H
#define IMAGESINKER_H
#include "DataSinker.h"
#include <QImage>
#include <QObject>
#include <QSaveFile>

class ImageSinker : public DataSinker {
public:
    explicit ImageSinker(const QString& baseSavePath);
    ~ImageSinker() override;

    QString provide_name() override;
    void consume_name(const QString& name) override;
    qint64 id_generator() override;
    QByteArray requestChunkForEncoding(quint64 offset, quint64 bytesForRead) override;
    quint64 size() override;
    bool receiveEnd() override;
    bool consumeChunkBuffer(const QByteArray& chunk) override;
    void sendEnd() override;
    void initMemoryBuffer(const QByteArray& chunk) override;
    QImage getImage() const; // 获取解析后的图像
    void resetSelf() override;

private:
    QString baseSavePath_;
    QString saveFilePath_;
    QSaveFile saveFile_;
    QByteArray buffer_; // 用于累积图像数据
    QImage image_;
    qint64 fileSize_ = 0;
    bool isReceiving_ = false;
};

#endif // IMAGESINKER_H
