#ifndef SESSION_H
#define SESSION_H
#include "SessionInfo.h"
#include <QObject>

class PeerConnection;
class DataProtocolizedController;
class DataSinker;
class ISinkerRouter;

class Session : public QObject {
    Q_OBJECT
public:
    explicit Session(PeerConnection* transport,
                     const SessionInfo& localName,
                     QObject* parent = nullptr);
    ~Session() override;
    int port_running() const;
    std::pair<QString, int> peerInfo() const;
    SessionInfo localName() const { return localInfo; }
    SessionInfo remoteName() const { return remoteInfo; }

    void sendText(const QString& text);
    void sendImage(const QImage& image);
    void sendFile(const QString& filePath);

    QString sessionID() const;

signals:
    void textReceived(const QString& text);
    void imageReceived(const QImage& okImage);
    void fileReceived(const QString& fileSaveAt);

    void connected(Session* s);
    void ready(Session* s, const SessionInfo& remoteName);
    void disconnected(Session* s);
    void error(Session* s, const QString& disp, int code);

    void sendProgress(Session* s, quint64 sent, quint64 total);
    void receiveProgress(Session* s, const QString& fileId, quint64 received, quint64 total);
private slots:
    // // ---- PeerConnection ----
    void onConnected();
    void onDisconnected();

private:
    void sinkerOk(DataSinker* sinker);
    void shake_hands_to_peers();
    void attempt_parse_hello(const QByteArray& e);

private:
    PeerConnection* transport;
    SessionInfo localInfo;
    SessionInfo remoteInfo;
    DataProtocolizedController* controller;
    bool communicate_ready { false };
};

#endif
