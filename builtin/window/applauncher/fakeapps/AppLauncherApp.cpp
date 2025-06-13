#include "AppLauncherApp.h"
#include "desktopmainwindow.h"

AppLauncherApp::AppLauncherApp(DesktopMainWindow* parent)
    : AppWidget(QPixmap(":/icons/sources/app_launcher.png"),
                "Launcher", parent) {
    AppLaunchLauncher* wrapper = new AppLaunchLauncher(parent);
    bindApp(wrapper);
    connect(wrapper, &AppLaunchLauncher::indicate_open_launch_window,
            this, &AppLauncherApp::do_daptch);
}

void AppLauncherApp::do_daptch() {
    emit indicate_open_launch_window();
    emit postAppStatus(AppStatus::AppOk);
}

AppLaunchLauncher::AppLaunchLauncher(DesktopMainWindow* parent)
    : ApplicationWrapper(parent, parent) {
}

void AppLaunchLauncher::depatch_app() {
    emit indicate_open_launch_window();
}
