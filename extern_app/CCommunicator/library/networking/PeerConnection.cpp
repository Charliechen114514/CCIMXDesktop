#include "PeerConnection.h"
#include <QTcpServer>
#include <QTcpSocket>
#include <QUuid>
PeerConnection::PeerConnection(QObject* parent)
    : QObject(parent)
    , uuid_marker(QUuid::createUuid().toString(QUuid::WithoutBraces)) {
    server_socket = new QTcpServer(this);
    connect(server_socket, &QTcpServer::newConnection,
            this, &PeerConnection::handleNewConnection);
}

PeerConnection::~PeerConnection() {
    disconnectFromPeer();
}

bool PeerConnection::availableSelfListen(const SelfInfo& info) {
    qDebug() << "Enter availableSelfListen";
    if (current_state != ConnectionState::Disconnected) {
        qWarning() << "Current Socket owns a connection already!"
                      "duplicate listening is not permitted!";
        return false;
    }

    if (server_socket->listen(QHostAddress::Any, info.port)) {
        qInfo() << "OK, server has been available in " << server_socket->serverPort();
        setState(ConnectionState::Listening);
        self_info = info;
        return true;
    }

    qCritical() << "Server listen failed! see the reason: " << server_socket->errorString();
    return false;
}

bool PeerConnection::connectToPeer(const PeerInfo& peerInfo) {
    qDebug() << "try Connect to peer: " << peerInfo.host_address << " " << peerInfo.target_port;
    if (current_state != ConnectionState::Disconnected
        && current_state != ConnectionState::Listening) {
        qWarning() << "Can not reset an already connections, try close it first";
        return false;
    }

    if (peer_socket) {
        qDebug() << "Peer socket not null, delete for reset";
        peer_socket->deleteLater();
        peer_socket = nullptr;
    }

    this->peer_info = peerInfo;
    peer_socket = new QTcpSocket(this);
    setupSocket(peer_socket);

    qDebug() << "Attempting to connect to" << peerInfo.host_address << ":" << peerInfo.target_port;
    setState(ConnectionState::Connecting);

    peer_socket->connectToHost(peerInfo.host_address, peerInfo.target_port);
    return true;
}

SelfInfo PeerConnection::selfInfo() const {
    return self_info;
}

PeerInfo PeerConnection::peerInfo() const {
    return peer_info;
}

PeerConnection::ConnectionState PeerConnection::state() const {
    return current_state;
}

bool PeerConnection::send_data(const QByteArray& raw_data) {
    if (current_state != ConnectionState::Connected || !peer_socket) {
        qWarning() << "Cannot send data: not connected.";
        return false;
    }
    // async write
    peer_socket->write(raw_data);
    return true;
}

void PeerConnection::disconnectFromPeer() {
    if (current_state == ConnectionState::Disconnected) {
        return;
    }
    setState(ConnectionState::Disconnected);
    if (peer_socket) {
        peer_socket->abort();
        peer_socket->deleteLater();
        peer_socket = nullptr;
    }
    if (server_socket->isListening()) {
        server_socket->close();
    }
    peer_info = {};
}

void PeerConnection::handleNewConnection() {
    qDebug() << "handleNewConnection is triggered!";
    if (current_state != ConnectionState::Listening || peer_socket) {
        // yes, we can not handle a new connnect
        // when we are not listening(including none open socket
        // and established)
        if (server_socket->hasPendingConnections()) {
            qWarning() << "New Connection is Coming in the P2P, "
                          "new connection will be abort "
                          "while old connection reserved!";
            QTcpSocket* extraSocket = server_socket->nextPendingConnection();
            extraSocket->abort();
            extraSocket->deleteLater();
        }
        return;
    }

    peer_socket = server_socket->nextPendingConnection();
    if (!peer_socket) {
        qCritical() << "Although New Connection is indicate to happen"
                       ", but fuckingly, nextPendingConnection create failed.";
        return;
    }

    qInfo() << "Init Client Socket OK, stop listening";
    server_socket->close();
    peer_info = PeerInfo { peer_socket->peerAddress().toString(), peer_socket->peerPort() };
    setupSocket(peer_socket);
    setState(ConnectionState::Connected);
    emit connected();
}

void PeerConnection::onSocketStateChanged(QAbstractSocket::SocketState socketState) {
    switch (socketState) {
    case QAbstractSocket::ConnectedState:
        if (current_state == ConnectionState::Connecting) {
            if (server_socket->isListening()) {
                server_socket->close();
            }
            setState(ConnectionState::Connected);
            emit connected();
        }
        break;
    case QAbstractSocket::UnconnectedState:
        if (current_state == ConnectionState::Connected || current_state == ConnectionState::Connecting) {
            disconnectFromPeer();
            emit disconnected();
        }
        break;
    default:
        break;
    }
}

void PeerConnection::onSocketError(QAbstractSocket::SocketError socketError) {
    if (socketError != QAbstractSocket::RemoteHostClosedError) {
        qCritical() << "Socket Error Occurs";
        emit errorOccurred(socketError);
    }
}

void PeerConnection::processSocketRead() {
    qDebug() << "Ok we get some messages in PeerConnection Level";
    if (peer_socket) {
        emit dataReceived(peer_socket->readAll());
    }
}

void PeerConnection::setupSocket(QTcpSocket* socket) {
    connect(socket, &QTcpSocket::stateChanged,
            this, &PeerConnection::onSocketStateChanged);
    connect(socket, &QTcpSocket::errorOccurred,
            this, &PeerConnection::onSocketError);
    connect(socket, &QTcpSocket::readyRead,
            this, &PeerConnection::processSocketRead);
    connect(socket, &QTcpSocket::bytesWritten,
            this, &PeerConnection::bytesWritten);
}

void PeerConnection::setState(ConnectionState newState) {
    if (current_state != newState) {
        current_state = newState;
        emit stateChanged(current_state);
    }
}
