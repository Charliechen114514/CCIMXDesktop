#include "DesktopUserInfo.h"
#include "UserInfo.h"
#include "core/desktop_dirent_manager/DesktopDirentLocationManager.h"
#include "library/qt_relative/fileio/QtFileIO.h"
#include <QFileInfo>
#include <QStandardPaths>
#include <QString>
namespace {
QString getUserName() {
#ifdef Q_OS_WIN
    QString name = QString::fromLocal8Bit(qgetenv("USERNAME"));
#else
    QString name = QString::fromLocal8Bit(qgetenv("USER"));
#endif
    qDebug() << "Try System name: " << name;
    if (!name.isEmpty())
        return name;
    qDebug() << "Try Writable Roots";
    // Fallback: extract from home directory
    QString homePath = QStandardPaths::writableLocation(QStandardPaths::HomeLocation);
    name = QFileInfo(homePath).fileName();
    if (!name.isEmpty())
        return name;

    qDebug() << "All failed! use default name";
    return "Charliechen114514";
}

}

DesktopUserInfo::DesktopUserInfo(DesktopDirentLocationManager* parent)
    : QObject { parent } {
    manager = parent;
}

void DesktopUserInfo::start_init() {
    if (manager->checkConfigExsited(ConfigureFileName::UserConfig)) {
        QString json_file = manager->queryConfigType(ConfigureFileName::UserConfig);
        QFile f(json_file);
        f.open(QIODevice::ReadOnly);
        if (f.isOpen()) {
            info = UserInfo::UserInfoBuilder::fromJson(f.readAll());
            if (info) {
                if (info->get_name().isEmpty()) {
                    qWarning() << "Parsing an empty name, "
                                  "use system default!";
                    info->set_name(getUserName());
                }

                if (!QtFileIOUtils::checkPathAndPermission(info->get_avatar(), PermissionType::Read)) {
                    qWarning() << "Parsing an unaccessible avator, "
                                  "use system default! "
                                  "and try to check the session: "
                               << info->get_avatar();
                    info->set_avator(":/avator/sources/avatar/user_avatar.png");
                }

                emit user_init_ok(*info);
                return;
            }
            qCritical() << "json file error parsing"
                           "failed to dumped the reading sessions"
                           " fall back to default sessions";

        } else {
            qCritical() << "Strangely json file error read! "
                           "failed to dumped the reading sessions"
                           " fall back to default sessions";
        }
    }
    qWarning() << "No Json file in " << manager->queryConfigType(ConfigureFileName::UserConfig)
               << "You can next time place templated json file in here, see configs/user/user_config.json for example :)";
    qInfo() << "As json file missing, init User info as default!";
    UserInfo::UserInfoBuilder builder;
    info = builder
               .set_email("example@charliechen.com")
               .set_phone_number("114514")
               .set_name(getUserName())
               .set_avatar(":/avator/sources/avatar/user_avatar.png")
               .build();
    emit user_init_ok(*info);
}
