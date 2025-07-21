#ifndef DESKTOPUSERINFO_H
#define DESKTOPUSERINFO_H
#include "UserInfo.h"
#include <QObject>
class DesktopDirentLocationManager;
class DesktopUserInfo : public QObject {
	Q_OBJECT
public:
    explicit DesktopUserInfo(DesktopDirentLocationManager* parent = nullptr);
public slots:
    void start_init(); ///< start init will scan the target file once
    inline UserInfo* get_info(){return info.get();} ///< get info, might be not inited!
signals:
    void user_init_ok(const UserInfo& info);

private:
    DesktopDirentLocationManager* manager;
    std::unique_ptr<UserInfo> info;
};

#endif // DESKTOPUSERINFO_H
