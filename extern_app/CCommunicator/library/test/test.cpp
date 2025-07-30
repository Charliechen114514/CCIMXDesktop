#include "PeerConnection.h"
#include <QCoreApplication>
#include <QDebug>
#include <QTimer>

int main(int argc, char* argv[]) {
    QCoreApplication a(argc, argv);
    qDebug() << "--- PeerConnection Test Starting ---";
    PeerConnection peer1;
    PeerConnection peer2;

    QObject::connect(&peer1, &PeerConnection::stateChanged, [](PeerConnection::ConnectionState state) {
        qDebug() << "[Peer 1] State changed to:" << state;
    });

    QObject::connect(&peer1, &PeerConnection::dataReceived, [&](const QByteArray& data) {
        qDebug() << "[Peer 1] Received data:" << data;
        qDebug() << "[Peer 1] Replying with 'World'...";
        peer1.send_data("World");
    });

    QObject::connect(&peer1, &PeerConnection::disconnected, []() {
        qDebug() << "[Peer 1] Successfully disconnected.";
    });

    // -- 配置 peer2 (客户端) --
    QObject::connect(&peer2, &PeerConnection::stateChanged, [](PeerConnection::ConnectionState state) {
        qDebug() << "[Peer 2] State changed to:" << state;
    });

    QObject::connect(&peer2, &PeerConnection::connected, [&]() {
        qDebug() << "[Peer 2] Successfully connected to Peer 1.";
        qDebug() << "[Peer 2] Sending 'Hello'...";
        peer2.send_data("Hello");
    });

    QObject::connect(&peer2, &PeerConnection::dataReceived, [&](const QByteArray& data) {
        qDebug() << "[Peer 2] Received reply:" << data;
        qDebug() << "[Peer 2] Test complete. Disconnecting...";
        // 步骤 5: 收到回复后，断开连接
        peer2.disconnectFromPeer();
    });

    QObject::connect(&peer2, &PeerConnection::disconnected, [&]() {
        qDebug() << "[Peer 2] Successfully disconnected.";
        qDebug() << "--- Test Finished ---";
        // 步骤 6: peer2 断开后，退出程序
        QTimer::singleShot(100, &a, &QCoreApplication::quit);
    });

    // 步骤 2: 启动 peer1 的监听，并让 peer2 连接它
    if (peer1.availableSelfListen({ 12345 })) {
        SelfInfo peer1Info = peer1.selfInfo();
        qDebug() << "[Main] Peer 1 is listening on" << peer1Info.port;

        PeerInfo targetInfo = { "127.0.0.1", peer1Info.port };
        qDebug() << "[Main] Instructing Peer 2 to connect to Peer 1...";
        peer2.connectToPeer(targetInfo);
    } else {
        qCritical() << "[Main] Peer 1 failed to listen. Test aborted.";
        return -1;
    }

    return a.exec();
}
