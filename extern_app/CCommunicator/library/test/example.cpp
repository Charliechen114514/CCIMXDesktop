#include "DataProtocolizedController.h"
#include "FileSinker.h"
#include "ImageSinker.h"
#include <QCoreApplication>
#include <QDebug>
#include <QFile>

int main(int argc, char* argv[]) {
    QCoreApplication app(argc, argv);

    QString imagePath = QString::fromLocal8Bit("./test.png");
    if (!QFile::exists(imagePath)) {
        qWarning() << "Image file does not exist:" << imagePath;
        return -1;
    }

    // 1. 发送端：FileSinker
    FileSinker sendSink(imagePath, 1024); // 每块1KB
    DataProtocolizedController sender(&sendSink);

    // 2. 接收端：ImageSinker
    QString tempDir = QDir::temp().filePath("image_receiver_demo");
    QDir().mkpath(tempDir);
    ImageSinker recvSink(tempDir);
    DataProtocolizedController receiver(&recvSink);

    // 3. 连接 frameReady 信号，把发送端数据传给接收端
    QObject::connect(&sender, &DataProtocolizedController::frameReady,
                     [&receiver](const QByteArray& frame) {
                         receiver.onBytes(frame);
                     });

    // 4. 连接调试信号
    QObject::connect(&sender, &DataProtocolizedController::sendProgress,
                     [](quint64 sent, quint64 total) {
                         qDebug() << "[SendProgress]" << sent << "/" << total;
                     });

    QObject::connect(&receiver, &DataProtocolizedController::receiveProgress,
                     [](const QString& fileId, quint64 received, quint64 total) {
                         qDebug() << "[ReceiveProgress]" << fileId << received << "/" << total;
                     });

    QObject::connect(&receiver, &DataProtocolizedController::parsingBad,
                     []() {
                         qWarning() << "[Receiver] Parsing bad!";
                     });

    QObject::connect(&receiver, &DataProtocolizedController::protocolError,
                     [](const QString& reason) {
                         qWarning() << "[Receiver] Protocol error:" << reason;
                     });

    // 5. 执行发送
    sender.sendData(1024);

    // 6. 接收端完成后检查结果
    QImage img = recvSink.getImage();
    if (!img.isNull()) {
        qDebug() << "[Demo] Image received successfully! Size:" << img.size();
        img.save("other.png");
    } else {
        qWarning() << "[Demo] Failed to load image from received data!";
    }

    return 0;
}
