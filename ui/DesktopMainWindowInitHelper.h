#ifndef DESKTOPMAINWINDOWINITHELPER_H
#define DESKTOPMAINWINDOWINITHELPER_H
class AutoStepIniter;
class CCIMX_DesktopSplashWindow;
class DesktopMainWindowInitHelper {
public:
    friend class DesktopMainWindow;
    static void run_init_session(
        DesktopMainWindow* mainWindow, CCIMX_DesktopSplashWindow* splash_window);

private:
    static void session_of_init_core(DesktopMainWindow* mainWindow, AutoStepIniter* initer);
    static void session_of_init_ui(DesktopMainWindow* mainWindow, AutoStepIniter* initer);
    static void session_of_init_server(DesktopMainWindow* mainWindow, AutoStepIniter* initer);
    static void session_of_init_plugins(DesktopMainWindow* mainWindow, AutoStepIniter* initer);
    static void session_of_later_init(DesktopMainWindow* mainWindow, AutoStepIniter* initer);
};

#endif // DESKTOPMAINWINDOWINITHELPER_H
