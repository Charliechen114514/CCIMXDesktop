#include "SessionHub.h"
#include "PeerConnection.h"
#include "SessionInfo.h"
#include "core/ConnectionUtils.h"
SessionHub::SessionHub(const SessionInfo& localName, QObject* parent)
    : QObject(parent)
    , localInfo(localName) {
    // m_router = new DataSinkerRouter;
}

std::vector<int> SessionHub::running_ports() const {
    std::vector<int> res;
    for (const auto& session : std::as_const(idmaps)) {
        res.emplace_back(session->port_running());
    }
    return res;
}

Session* SessionHub::createSessionActive(const SessionInfo& info, const PeerInfo& peers) {
    PeerConnection* pc = new PeerConnection(this);
    auto* s = new Session(pc, info, this);
    sessions_containers.insert(s, s);
    idmaps.insert(pc->uuid(), s);

    connect(s, &Session::connected, this, &SessionHub::onSessionConnected);
    connect(s, &Session::ready, this, &SessionHub::onSessionReady);
    connect(s, &Session::sendProgress, this, &SessionHub::onSessionSendProgress);
    connect(s, &Session::receiveProgress, this, &SessionHub::onSessionReceiveProgress);
    connect(s, &Session::disconnected, this, &SessionHub::onSessionDisconnected);
    connect(s, &Session::error, this, &SessionHub::onSessionError);
    connect(s, &Session::textReceived, this, [this, s](const QString& text) {
        emit this->textReceived(s, text);
    });
    connect(s, &Session::imageReceived, this, [this, s](const QImage& array) {
        emit this->imageReceived(s, array);
    });
    connect(s, &Session::fileReceived, this, [this, s](const QString& text) {
        emit this->fileReceived(s, text);
    });
    pc->connectToPeer(peers);
    return s;
}

Session* SessionHub::passiveSessionListen() {
    PeerConnection* pc = new PeerConnection(this);
    auto* s = new Session(pc, localInfo, this);
    sessions_containers.insert(s, s);
    idmaps.insert(pc->uuid(), s);
    connect(s, &Session::connected, this, &SessionHub::onSessionConnected);
    connect(s, &Session::ready, this, &SessionHub::onSessionReady);
    connect(s, &Session::sendProgress, this, &SessionHub::onSessionSendProgress);
    connect(s, &Session::receiveProgress, this, &SessionHub::onSessionReceiveProgress);
    connect(s, &Session::disconnected, this, &SessionHub::onSessionDisconnected);
    connect(s, &Session::error, this, &SessionHub::onSessionError);
    connect(s, &Session::textReceived, this, [this, s](const QString& text) {
        emit this->textReceived(s, text);
    });
    connect(s, &Session::imageReceived, this, [this, s](const QImage& array) {
        emit this->imageReceived(s, array);
    });
    connect(s, &Session::fileReceived, this, [this, s](const QString& text) {
        emit this->fileReceived(s, text);
    });

    auto port = PortUtils::generate(1024, 65535, running_ports());
    bool ok = pc->availableSelfListen({ port });
    if (!ok) {
        qWarning() << "Failed to listen on port" << port;
        s->deleteLater();
    }
    connect(pc, &PeerConnection::connected,
            this, &SessionHub::passiveSessionListen);
    qInfo() << "Listening at port:" << port;
    emit next_available_port(port);
    return s;
}

Session* SessionHub::queryFromUuid(const QString& uuid) {
    return idmaps.value(uuid);
}

void SessionHub::onSessionConnected(Session* s) {
    // Session internally sends NAME:localName upon connection
    qDebug() << "Session connected! UUID: " << s->sessionID();
}

void SessionHub::onSessionReady(Session* s, const SessionInfo& remoteName) {
    emit sessionReady(s, remoteName);
    qDebug() << "Session is Ready! UUID: " << s->sessionID() << " With remote "
             << remoteName.nickName;
}

void SessionHub::onSessionSendProgress(Session* s, quint64 sent, quint64 total) {
    emit sendProgress(s, sent, total);
}

void SessionHub::onSessionReceiveProgress(Session* s, const QString& fileId,
                                          quint64 received, quint64 total) {
    emit receiveProgress(s, fileId, received, total);
}

void SessionHub::onSessionDisconnected(Session* s) {
    emit disconnected(s);
    sessions_containers.remove(s);
    s->deleteLater();
}

void SessionHub::onSessionError(Session* s, const QString& errorString, int code) {
    qDebug() << "[SessionHub] onSessionError happens for s, uuid: " << s->sessionID()
             << errorString << " code: " << code;
    emit error(s, errorString, code);
}
