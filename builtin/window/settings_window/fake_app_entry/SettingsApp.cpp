#include "SettingsApp.h"
#include "desktopmainwindow.h"
SettingsLaunch::SettingsLaunch(DesktopMainWindow* parent)
    : ApplicationWrapper(parent, parent) {
}

SettingsApp::SettingsApp(DesktopMainWindow* parent)
    : AppWidget(QPixmap(":/icons/sources/settings.png"), "Settings", parent) {
    SettingsLaunch* wrapper = new SettingsLaunch(parent);
    bindApp(wrapper);
    connect(wrapper, &SettingsLaunch::indicate_open_settings_window,
            this, &SettingsApp::do_daptch);
}

void SettingsApp::do_daptch() {
    emit indicate_open_settings_window();
    emit postAppStatus(AppStatus::AppOk);
}

void SettingsLaunch::depatch_app() {
    emit indicate_open_settings_window();
}
