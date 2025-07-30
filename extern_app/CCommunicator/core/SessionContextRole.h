#ifndef SESSIONCONTEXTROLE_H
#define SESSIONCONTEXTROLE_H
#include <qnamespace.h>
enum ContextRole {
    RoleAvatar = Qt::UserRole + 1,
    RoleName,
    RoleLastMsg,
    RoleTime,
    RoleUnread,
    RoleUuid
};

#endif // SESSIONCONTEXTROLE_H
