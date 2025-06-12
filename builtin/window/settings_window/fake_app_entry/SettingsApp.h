#ifndef SETTINGSAPP_H
#define SETTINGSAPP_H
#include "app_wrapper/applicationwrapper.h"
#include "appwidget.h"
class DesktopMainWindow;
class SettingsLaunch : public ApplicationWrapper {
    Q_OBJECT
public:
    SettingsLaunch(DesktopMainWindow* parent);
    void depatch_app() override;
signals:
    void indicate_open_settings_window();
};

class SettingsApp : public AppWidget {
    Q_OBJECT
public:
    explicit SettingsApp(DesktopMainWindow* parent = nullptr);
    void do_daptch() override;
signals:
    void indicate_open_settings_window();
};

#endif // SETTINGSAPP_H
