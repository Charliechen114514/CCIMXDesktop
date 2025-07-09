#ifndef DESKTOPDIRENTLOCATIONMANAGER_H
#define DESKTOPDIRENTLOCATIONMANAGER_H
#include "DesktopDirentInfoSettings.h"
#include <QObject>
class DesktopMainWindow;
class DesktopDirentLocationManager : public QObject {
	Q_OBJECT
public:
    explicit DesktopDirentLocationManager(const QString& root_path, DesktopMainWindow* parent = nullptr);
    void checkSelfOnce();
    QString queryFromType(const DesktopDirentType type);
    QString queryFromType(const DesktopServerType serverType);
    bool checkComponentFolder(const DesktopDirentType type);
    bool checkServerFolder(const DesktopServerType serverType);

signals:
    void missingDirentFolder(const QString& folder, const DesktopDirentType type);
    void missingServerFolder(const QString& folder, const DesktopServerType type);

private:
    QString root_path;
    DesktopMainWindow* bindingWindow;
    void check_root_path_sessions();
    void iterate_check_basefolder_components(const DesktopDirentType t, const QString& metaMessage);
    void iterate_check_server_components(const DesktopServerType t, const QString& metaMessage);
    void check_up_toast_infomations();
};

#endif // DESKTOPDIRENTLOCATIONMANAGER_H
