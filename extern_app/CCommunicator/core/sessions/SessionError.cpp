#include "SessionError.h"

void SessionError::transfer(QAbstractSocket::SocketError e, QString& errorMessage, int& errorCode) {
    switch (e) {
    case QAbstractSocket::ConnectionRefusedError:
        errorCode = 1;
        errorMessage = "Connection refused.";
        break;
    case QAbstractSocket::RemoteHostClosedError:
        errorCode = 2;
        errorMessage = "The remote host closed the connection.";
        break;
    case QAbstractSocket::HostNotFoundError:
        errorCode = 3;
        errorMessage = "The host address was not found.";
        break;
    case QAbstractSocket::SocketAccessError:
        errorCode = 4;
        errorMessage = "A socket access error occurred.";
        break;
    case QAbstractSocket::SocketResourceError:
        errorCode = 5;
        errorMessage = "The socket operation failed because the system lacked the necessary resources.";
        break;
    case QAbstractSocket::SocketTimeoutError:
        errorCode = 6;
        errorMessage = "The socket operation timed out.";
        break;
    case QAbstractSocket::DatagramTooLargeError:
        errorCode = 7;
        errorMessage = "The datagram was larger than the system's limit.";
        break;
    case QAbstractSocket::NetworkError:
        errorCode = 8;
        errorMessage = "A network error occurred.";
        break;
    case QAbstractSocket::AddressInUseError:
        errorCode = 9;
        errorMessage = "The address is already in use.";
        break;
    case QAbstractSocket::SocketAddressNotAvailableError:
        errorCode = 10;
        errorMessage = "The requested socket address is not available.";
        break;
    case QAbstractSocket::UnsupportedSocketOperationError:
        errorCode = 11;
        errorMessage = "The requested socket operation is not supported.";
        break;
    case QAbstractSocket::UnfinishedSocketOperationError:
        errorCode = 12;
        errorMessage = "A previous socket operation has not finished yet.";
        break;
    case QAbstractSocket::ProxyAuthenticationRequiredError:
        errorCode = 13;
        errorMessage = "Proxy authentication is required.";
        break;
    case QAbstractSocket::SslHandshakeFailedError:
        errorCode = 14;
        errorMessage = "The SSL/TLS handshake failed.";
        break;
    case QAbstractSocket::ProxyConnectionRefusedError:
        errorCode = 15;
        errorMessage = "The proxy connection was refused.";
        break;
    case QAbstractSocket::ProxyConnectionClosedError:
        errorCode = 16;
        errorMessage = "The proxy connection was closed.";
        break;
    case QAbstractSocket::ProxyConnectionTimeoutError:
        errorCode = 17;
        errorMessage = "The proxy connection timed out.";
        break;
    case QAbstractSocket::ProxyNotFoundError:
        errorCode = 18;
        errorMessage = "The proxy host was not found.";
        break;
    case QAbstractSocket::ProxyProtocolError:
        errorCode = 19;
        errorMessage = "The proxy protocol is invalid.";
        break;
    case QAbstractSocket::OperationError:
        errorCode = 20;
        errorMessage = "The operation failed due to an error.";
        break;
    case QAbstractSocket::SslInternalError:
        errorCode = 21;
        errorMessage = "An internal SSL error occurred.";
        break;
    case QAbstractSocket::SslInvalidUserDataError:
        errorCode = 22;
        errorMessage = "Invalid user data was provided to the SSL library.";
        break;
    case QAbstractSocket::TemporaryError:
        errorCode = 23;
        errorMessage = "A temporary error occurred.";
        break;
    case QAbstractSocket::UnknownSocketError:
    default:
        errorCode = 99; // Default value, or set as needed
        errorMessage = "An unknown socket error occurred.";
        break;
    }
}
