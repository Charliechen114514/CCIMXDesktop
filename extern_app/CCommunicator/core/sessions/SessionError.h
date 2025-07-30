#ifndef SESSIONERROR_H
#define SESSIONERROR_H
#include <QAbstractSocket>
#include <QString>

namespace SessionError {
void transfer(QAbstractSocket::SocketError e, QString& errorMessage, int& code);

class NameInvalid : public std::runtime_error {
public:
    NameInvalid()
        : std::runtime_error("Name is invalid!") { }
};

};

#endif // SESSIONERROR_H
