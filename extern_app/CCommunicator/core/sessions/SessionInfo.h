#ifndef SESSIONINFO_H
#define SESSIONINFO_H
#include <QString>
class SessionInfo {
public:
    QString nickName;
    SessionInfo() = default;
    SessionInfo(const QByteArray& protocol_string);
    QByteArray toProtocalString() const;
};

#endif // SESSIONINFO_H
