#ifndef SESSIONHUB_H
#define SESSIONHUB_H

#include "Session.h"
#include "SessionInfo.h"
#include <QHash>
#include <QMap>
#include <QObject>
#include <QPointer>
struct PeerInfo;
class SessionHub : public QObject {
    Q_OBJECT
public:
    explicit SessionHub(const SessionInfo& localName, QObject* parent = nullptr);
    ~SessionHub() override = default;
    std::vector<int> running_ports() const;
    Session* createSessionActive(const SessionInfo& info, const PeerInfo& peers);
    Session* passiveSessionListen();
    Session* queryFromUuid(const QString& uuid);

signals:
    void next_available_port(const int port);
    void sessionReady(Session* s, const SessionInfo& remoteName);

    void sendProgress(Session* s, quint64 sent, quint64 total);
    void receiveProgress(Session* s, const QString& fileId, quint64 received, quint64 total);
    void disconnected(Session* s);
    void error(Session* s, const QString& errorString, int code);

    // datas
    void textReceived(Session* s, const QString& text);
    void imageReceived(Session* s, const QImage& imageBytes);
    void fileReceived(Session* s, const QString& fileSaveAt);

private slots:
    void onSessionConnected(Session* s);
    void onSessionReady(Session* s, const SessionInfo& remoteName);
    void onSessionSendProgress(Session* s, quint64 sent, quint64 total);
    void onSessionReceiveProgress(Session* s, const QString& fileId, quint64 received, quint64 total);
    void onSessionDisconnected(Session* s);
    void onSessionError(Session* s, const QString& errorString, int code);

private:
    SessionInfo localInfo;
    // ISinkerRouter* m_router;
    QMap<QString, Session*> idmaps;
    QHash<Session*, QPointer<Session>> sessions_containers;
};

#endif // SESSIONHUB_H
