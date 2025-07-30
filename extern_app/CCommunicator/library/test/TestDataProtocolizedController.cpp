#pragma once

#include "DataHeader.h"
#include "DataProtocolizedController.h"
#include "ImageSinker.h"
#include "MemorySinker.h"
#include <QtTest/QtTest>

class TestDataProtocolizedController : public QObject {
    Q_OBJECT
private slots:
    void testMemoryTransfer();
    void testImageTransfer();
};

void TestDataProtocolizedController::testMemoryTransfer() {
    // 1. 构造发送端 MemorySinker
    MemorySinker sendSink("test_memory_send");
    QByteArray testData = "Hello DataProtocolizedController!";
    sendSink.consumeChunkBuffer(testData);

    // 2. 构造接收端 MemorySinker
    MemorySinker recvSink("test_memory_recv");

    DataProtocolizedController sender(&sendSink);
    DataProtocolizedController receiver(&recvSink);

    // 捕获frameReady信号并立即传递给receiver
    QObject::connect(&sender, &DataProtocolizedController::frameReady,
                     [&receiver](const QByteArray& frame) {
                         receiver.onBytes(frame);
                     });

    // 3. 执行发送
    sender.sendData(8); // 每次 8 字节分块

    // 4. 检查接收端结果
    QVERIFY(recvSink.size() == testData.size());
    QCOMPARE(recvSink.getBuffer(), testData);
}

void TestDataProtocolizedController::testImageTransfer() {
    // 1. 构造一个小图像并编码成 QByteArray
    QImage img(4, 4, QImage::Format_RGB32);
    img.fill(Qt::green);
    QByteArray imgBytes;
    QBuffer buffer(&imgBytes);
    buffer.open(QIODevice::WriteOnly);
    QVERIFY(img.save(&buffer, "PNG"));

    // 2. 构造发送端 MemorySinker，作为图片数据的载体
    MemorySinker sendSink("image_data");
    sendSink.consumeChunkBuffer(imgBytes);

    // 3. 构造接收端 ImageSinker
    QTemporaryDir tmpDir;
    QVERIFY(tmpDir.isValid());
    ImageSinker recvSink(tmpDir.path());

    DataProtocolizedController sender(&sendSink);
    DataProtocolizedController receiver(&recvSink);

    QObject::connect(&sender, &DataProtocolizedController::frameReady,
                     [&receiver](const QByteArray& frame) {
                         receiver.onBytes(frame);
                     });

    // 4. 执行发送
    sender.sendData(32); // 每次 32 字节分块

    // 5. 验证接收端是否成功还原
    QVERIFY(recvSink.getImage().size() == img.size());
    QVERIFY(!recvSink.getImage().isNull());
}

QTEST_MAIN(TestDataProtocolizedController)
#include "TestDataProtocolizedController.moc"
