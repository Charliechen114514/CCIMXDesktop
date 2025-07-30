#pragma once
#include "NetInfo.h"
#include <QAbstractSocket>
#include <QObject>
class QTcpSocket; ///< socket passive
class QTcpServer; ///< socket positive

class PeerConnection : public QObject {
    Q_OBJECT
public:
    /**
     * @enum ConnectionState
     * @brief Defines the current state of the peer connection.
     */
    enum class ConnectionState {
        Disconnected, ///< No active connection.
        Listening, ///< Listening for an incoming connection.
        Connecting, ///< Attempting to connect to a peer.
        Connected ///< An active connection is established.
    };

    Q_ENUM(ConnectionState); // register to the Qt Metas

    explicit PeerConnection(QObject* parent);
    ~PeerConnection();
    Q_DISABLE_COPY_MOVE(PeerConnection);

    bool availableSelfListen(const SelfInfo& info); ///< listen for the P2P available
    bool connectToPeer(const PeerInfo& peerInfo);

    SelfInfo selfInfo() const;
    /**
     * @brief Gets the information of the connected remote peer.
     * @return A PeerInfo object for the connected peer. Returns an invalid object if not connected.
     */
    PeerInfo peerInfo() const;
    /**
     * @brief Returns the current state of the connection.
     */
    ConnectionState state() const;

    /**
     * @brief Asynchronously sends data to the connected peer.
     * @param data The QByteArray data to send.
     * @return True if the data was queued for sending, false if there is no active connection.
     */
    bool send_data(const QByteArray& raw_data);

    /**
     * @brief Closes the current connection and stops listening.
     * Resets the object to its initial state.
     */
    void disconnectFromPeer();

    /**
     * @brief get the only one uuid
     * @return
     */
    const QString uuid() const { return uuid_marker; }

signals:
    /**
     * @brief Emitted when the connection state changes.
     * @param state The new state of the connection.
     */
    void stateChanged(PeerConnection::ConnectionState state);

    /**
     * @brief Emitted when a connection is successfully established.
     */
    void connected();

    /**
     * @brief Emitted when the connection is terminated.
     */
    void disconnected();

    /**
     * @brief Emitted when data is received from the peer.
     * @param data The data received.
     */
    void dataReceived(const QByteArray& data);

    /**
     * @brief Emitted to report the result of a send operation.
     * @param bytesWritten The number of bytes successfully written to the socket.
     */
    void bytesWritten(qint64 bytesWritten);

    /**
     * @brief Emitted when a network error occurs.
     * @param socketError The specific error code.
     */
    void errorOccurred(QAbstractSocket::SocketError socketError);

private slots:
    /**
     * @brief handle the session of new connections
     */
    void handleNewConnection();
    /**
     * @brief process the socket changes
     * @param socketState
     */
    void onSocketStateChanged(QAbstractSocket::SocketState socketState);
    /**
     * @brief onSocketError handle the socket error
     * @param socketError
     */
    void onSocketError(QAbstractSocket::SocketError socketError);
    /**
     * @brief processSocketRead
     */
    void processSocketRead();

private:
    /**
     * @brief setupSocket set the socket once
     * @param socket what socket
     */
    void setupSocket(QTcpSocket* socket);
    /**
     * @brief setState
     * @param newState
     */
    void setState(ConnectionState newState);
    ConnectionState current_state { ConnectionState::Disconnected };
    QTcpServer* server_socket {};
    QTcpSocket* peer_socket {};
    PeerInfo peer_info;
    SelfInfo self_info;
    const QString uuid_marker;
};
