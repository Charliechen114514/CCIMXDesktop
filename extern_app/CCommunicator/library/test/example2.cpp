#include <QCoreApplication>
#include <QDebug>
#include <QHostAddress>
#include <QTimer>

#include "DataProtocolizedController.h"
#include "MemorySinker.h"
#include "PeerConnection.h"

static constexpr quint16 kPort = 55555;

int main(int argc, char* argv[]) {
    QCoreApplication app(argc, argv);

    // -------- 1) 发送端：DataProtocolizedController + MemorySinker（可替换成 FileSinker） --------
    auto* sendSink = new MemorySinker("sender_mem");
    sendSink->consumeChunkBuffer(QByteArray("Hello PeerConnection + DPC!")); // 准备待发送数据

    DataProtocolizedController senderController(sendSink);

    // -------- 2) 接收端：DataProtocolizedController + MemorySinker（可替换成 ImageSinker） --------
    auto* recvSink = new MemorySinker("receiver_mem");
    DataProtocolizedController receiverController(recvSink);

    // -------- 3) 两个 PeerConnection：server(接收端) & client(发送端) --------
    PeerConnection serverPeer;
    PeerConnection clientPeer;

    // 3.1 server 监听
    SelfInfo selfInfo;
    selfInfo.port = kPort;
    if (!serverPeer.availableSelfListen(selfInfo)) {
        qCritical() << "serverPeer listen failed";
        return -1;
    }

    QObject::connect(&serverPeer, &PeerConnection::stateChanged,
                     [](PeerConnection::ConnectionState st) {
                         qDebug() << "[server] stateChanged:" << int(st);
                     });

    // 3.2 client 连接到 server
    PeerInfo peerInfo;
    peerInfo.host_address = "127.0.0.1";
    peerInfo.target_port = selfInfo.port;

    QObject::connect(&clientPeer, &PeerConnection::stateChanged,
                     [](PeerConnection::ConnectionState st) {
                         qDebug() << "[client] stateChanged:" << int(st);
                     });

    if (!clientPeer.connectToPeer(peerInfo)) {
        qCritical() << "clientPeer connectToPeer failed";
        return -1;
    }

    // -------- 4) 桥接：frameReady -> clientPeer.send_data --------
    QObject::connect(&senderController, &DataProtocolizedController::frameReady,
                     &clientPeer, [&clientPeer](const QByteArray& frame) {
                         clientPeer.send_data(frame);
                     });

    // -------- 5) 桥接：serverPeer.dataReceived -> receiverController.onBytes --------
    QObject::connect(&serverPeer, &PeerConnection::dataReceived,
                     &receiverController, &DataProtocolizedController::onBytes);

    // -------- 6) 一些调试信号 --------
    QObject::connect(&senderController, &DataProtocolizedController::sendProgress,
                     [](quint64 sent, quint64 total) {
                         qDebug() << "[sender] sendProgress:" << sent << "/" << total;
                     });
    QObject::connect(&receiverController, &DataProtocolizedController::receiveProgress,
                     [](const QString& fid, quint64 received, quint64 total) {
                         qDebug() << "[receiver] receiveProgress:" << fid << received << "/" << total;
                     });
    QObject::connect(&receiverController, &DataProtocolizedController::protocolError,
                     [](const QString& reason) {
                         qWarning() << "[receiver] protocolError:" << reason;
                     });
    QObject::connect(&receiverController, &DataProtocolizedController::parsingBad,
                     []() {
                         qWarning() << "[receiver] parsingBad";
                     });

    // -------- 7) client 连接成功后开始发送 --------
    QObject::connect(&clientPeer, &PeerConnection::connected, [&]() {
        qDebug() << "[client] connected, start to send...";
        senderController.sendData(8); // 按 8 字节分块发送
    });

    // -------- 8) 收尾检查 --------
    QTimer::singleShot(2000, [&]() {
        auto* memRecv = dynamic_cast<MemorySinker*>(recvSink);
        if (memRecv) {
            qDebug() << "[final] received size =" << memRecv->size()
                     << "content =" << memRecv->getBuffer();
        }
        app.quit();
    });

    return app.exec();
}
