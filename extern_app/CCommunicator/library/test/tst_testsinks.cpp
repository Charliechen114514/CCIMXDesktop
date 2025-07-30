// TestDataSinker.h
#pragma once

#include "ImageSinker.h"
#include "MemorySinker.h"
#include <QBuffer>
#include <QFile>
#include <QImage>
#include <QTemporaryDir>
#include <QtTest/QtTest>
class TestDataSinker : public QObject {
    Q_OBJECT
private slots:
    void testMemorySinker_basic();
    void testImageSinker_basic();
};

void TestDataSinker::testMemorySinker_basic() {
    MemorySinker memSink("test_mem");

    QCOMPARE(memSink.provide_name(), QString("test_mem"));

    memSink.consume_name("new_name");
    QCOMPARE(memSink.provide_name(), QString("new_name"));

    QByteArray data("Hello, this is a test data!");
    QVERIFY(memSink.consumeChunkBuffer(data));
    QCOMPARE(memSink.size(), quint64(data.size()));

    auto chunk = memSink.requestChunkForEncoding(0, 5);
    QCOMPARE(chunk, QByteArray("Hello"));

    QVERIFY(memSink.receiveEnd());

    memSink.sendEnd();
    QCOMPARE(memSink.size(), quint64(0));
}

void TestDataSinker::testImageSinker_basic() {
    // 创建临时目录存图像
    QTemporaryDir tempDir;
    QVERIFY(tempDir.isValid());

    QString basePath = tempDir.path();
    ImageSinker imgSink(basePath);

    // 模拟名称输入
    imgSink.consume_name("test.png");
    QVERIFY(!imgSink.provide_name().isEmpty());

    // 准备一张简单的 QImage，转成 QByteArray
    QImage img(10, 10, QImage::Format_RGB32);
    img.fill(Qt::red);

    QByteArray imgBytes;
    QBuffer buffer(&imgBytes);
    buffer.open(QIODevice::WriteOnly);
    QVERIFY(img.save(&buffer, "PNG"));
    buffer.close();

    // 分块发送数据模拟
    const int chunkSize = 5;
    int sent = 0;
    while (sent < imgBytes.size()) {
        int size = qMin(chunkSize, imgBytes.size() - sent);
        QByteArray chunk = imgBytes.mid(sent, size);
        QVERIFY(imgSink.consumeChunkBuffer(chunk));
        sent += size;
    }

    // 结束接收
    QVERIFY(imgSink.receiveEnd());

    // 验证图片加载成功
    QImage loadedImg = imgSink.getImage();
    QVERIFY(!loadedImg.isNull());
    QCOMPARE(loadedImg.size(), img.size());

    imgSink.sendEnd();
}

QTEST_MAIN(TestDataSinker)
#include "tst_testsinks.moc"
