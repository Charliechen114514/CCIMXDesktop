#include "DesktopMainWindowInitHelper.h"
#include "TopSideBarWidget.h"
#include "app_wrapper/pagesetuper.h"
#include "builtin/core/global_clock_src/GlobalClockSources.h"
#include "builtin/core/netability_scanner/NetAbilityScanner.h"
#include "builtin/page/homepage.h"
#include "builtin/window/applauncher/ApplicationLauncherMainWindow.h"
#include "builtin/window/settings_window/SettingsWindow.h"
#include "core/desktop_dirent_manager/DesktopDirentLocationManager.h"
#include "core/page_switching_limiter/PageSwitchingLimiter.h"
#include "core/server/plugin_server/DesktopPluginServer.h"
#include "core/server/server_hooks/DesktopCardHook.h"
#include "core/server/toast_file_gen_and_receiver/ToastPostServer.h"
#include "core/users/DesktopUserInfo.h"
#include "desktop_settings.h"
#include "desktopmainwindow.h"
#include "desktoptoast.h"
#include "downdockwidget.h"
#include "ui/fast_settings/FastSettingsWidget.h"
#include "library/qt_relative/auto_step_init/AutoStepInitTask.h"
#include "library/qt_relative/auto_step_init/AutoStepIniter.h"
#include "library/qt_relative/mouse_press_manager/MouseManager.h"
#include "library/qt_relative/mouse_press_manager/MouseProcessor.h"
#include "library/qt_relative/mouse_press_manager/MouseRecorder.h"
#include "pagefactory.h"
#include "ui/splash_window/CCIMX_DesktopSplashWindow.h"
#include <functional>

void DesktopMainWindowInitHelper::
    run_init_session(DesktopMainWindow* mainWindow, CCIMX_DesktopSplashWindow* splash_window) {
    AutoStepIniter* initer = new AutoStepIniter(mainWindow);
    QObject::connect(initer, &AutoStepIniter::updateProgress,
                     splash_window, &CCIMX_DesktopSplashWindow::handle_accessment);
    session_of_init_core(mainWindow, initer);
    session_of_init_ui(mainWindow, initer);
    session_of_init_server(mainWindow, initer);
    session_of_init_plugins(mainWindow, initer);
    session_of_later_init(mainWindow, initer);

    initer->run_init_session();
}

void DesktopMainWindowInitHelper::session_of_init_core(
    DesktopMainWindow* mainWindow, AutoStepIniter* initer) {
    const std::pair<std::function<void()>, const char*> sessions[] = {
        // static ui
        { [mainWindow]() {
             mainWindow->setup_static_ui();
         },
          "Setting up Desktop Static Ui" },

        // mouse event
        { [mainWindow]() {
             mainWindow->mouseManager = std::make_shared<MouseManager>();
             MouseProcessor* processor = new MouseProcessor(
                 [mainWindow](MouseRecorder* recorder) -> bool {
                       const QPoint diff = recorder->press - recorder->release;
                       return qAbs(diff.x()) >=  mainWindow->slide_limitive; },
                 [mainWindow](MouseRecorder* recorder) -> bool {
                       const QPoint diff = recorder->press - recorder->release;
                       diff.x() < 0 ?  mainWindow->to_next_page() :  mainWindow->to_prev_page();
                       return true; });
             processor->setName("PageSliderProcessor");
             mainWindow->mouseManager->register_processor(processor);

             MouseProcessor* updown_processor = new MouseProcessor(
                 [mainWindow](MouseRecorder* recorder) -> bool {
                              const QPoint diff = recorder->press - recorder->release;
                              return qAbs(diff.y()) >= mainWindow->tool_settings_bar_slide_limitive; },
                 [mainWindow](MouseRecorder* recorder) -> bool {
                                const QPoint diff = recorder->press - recorder->release;
                                if(diff.y() < 0){
                                    mainWindow->fastSettingsWidget->slideDown();
                                }else{
                                    mainWindow->fastSettingsWidget->slideUp();
                                }
                              return true; });
             updown_processor->setName("ToolSettingsProcessor");
             mainWindow->mouseManager->register_processor(updown_processor);
         },
          "Setting up MouseManager" },

        // desktop location
        { [mainWindow]() { mainWindow->locationManager = new DesktopDirentLocationManager(_DESKTOP_ROOT_PATH); },
          "Setting up Desktop Global Core Sources" },

        // global sources of networks
        { [mainWindow]() { mainWindow->scanner = new NetAbilityScanner(mainWindow); },
          "Setting up Desktop Network Scanner Core Sources" },

        // global clk src
        { [mainWindow]() { mainWindow->clock = new GlobalClockSources(mainWindow); },
          "Setting up Desktop Clock Sources" },

        // run basic settings
        { [mainWindow]() {
             mainWindow->slide_limitive = PageSwitchingLimiterParams::DEF_POSX;
             mainWindow->tool_settings_bar_slide_limitive = 100;
         },
          "Importing must settings for desktop windows" }
    };

    for (const auto& session : sessions) {
        auto [functor, name] = session;
        initer->install_tasks(std::make_shared<AutoStepInitTask>(std::move(functor), QString::fromUtf8(name)));
    }
}

void DesktopMainWindowInitHelper::session_of_init_ui(DesktopMainWindow* mainWindow, AutoStepIniter* initer) {

    const std::pair<std::function<void()>, const char*> sessions[] = {
        // desktop basic components init
        { [mainWindow]() {
             mainWindow->downDockWidget()->set_parent_window(mainWindow);
         },
          "Hooking the downdock Widget" },

        { [mainWindow]() {
             mainWindow->toast = new DesktopToast(mainWindow);
         },
          "Installing the Desktop toast component" },

        { [mainWindow]() {
             mainWindow->wallpaper_engine = new WallPaperEngine(mainWindow);
         },
          "Installing the Desktop wallpaper engine component" },

        { [mainWindow]() {
             mainWindow->appLauncherWindow = new ApplicationLauncherMainWindow(mainWindow);
         },
          "Installing the Desktop application launcher window component" },

        { [mainWindow]() {
             mainWindow->topSideBar()->installHookedWindow(mainWindow);
         },
          "Hooking the top-side widget bar to main window" },

        { [mainWindow]() {
             mainWindow->settingsWindow = new SettingsWindow(mainWindow);
         },
          "Initializing the Settings window" },

        { [mainWindow]() {
             mainWindow->user_info = new DesktopUserInfo(mainWindow->locationManager);
             mainWindow->user_info->start_init();
         },
          "Initializing user information (DesktopUserInfo) with automatic startup" },

        // Home Page
        { [mainWindow]() {
             qDebug() << "Setup HomePage";
             mainWindow->homePage = PageFactory::build_home_page(mainWindow);
             qInfo() << "Home Page is Ready!";
         },
          "Setup the Home Page" },

        // Builtin Apps Pages
        { [mainWindow]() {
             qDebug() << "Creating Entries for the Builtin Apps";
             PageSetuper::create_specified_page(mainWindow->stackedWidget(), mainWindow->homePage);
         },
          "Creating Entries for the Builtin Apps" },

        // Internal Apps
        { [mainWindow]() {
             mainWindow->app_widgets << PageSetuper::create_builtin_apps(mainWindow);
             qInfo() << "Bulitin Apps is Ready!";
         },
          "Creating Entries for the Internal Apps" },
        { [mainWindow]() {
             mainWindow->app_widgets << PageSetuper::create_internal_apps(mainWindow);
             qInfo() << "Internal Apps is Ready!";
         },
          "Creating Entries for the Third Party Apps" },
        { [mainWindow]() {
             mainWindow->app_widgets << PageSetuper::create_real_app(mainWindow);
             qInfo() << "Third Party Apps is Ready!";
         },
          "Initing the DockWidgets" },
        { [mainWindow]() {
             qInfo() << "Dock Widgets Inits OK!";
             mainWindow->setup_default_dock();
         },
          "Installing Default Apps" },
        {
          [mainWindow](){
             qInfo() << "Hooking fast setitngs ";
             mainWindow->fastSettingsWidget = new FastSettingsWidget(mainWindow);
        }, "Fast Settings Tool Hooking"}
    };

    for (const auto& session : sessions) {
        auto [functor, name] = session;
        initer->install_tasks(std::make_shared<AutoStepInitTask>(std::move(functor), name));
    }
}


#include "core/server/timer_server/timerservermonitoring.h"
#include "core/server/timer_server/screen_server/screendetectorserver.h"
void DesktopMainWindowInitHelper::session_of_init_server(DesktopMainWindow* mainWindow, AutoStepIniter* initer) {
    const std::pair<std::function<void()>, const char*> sessions[] = {
        { [mainWindow]() {
             mainWindow->servers.emplaceBack(new ToastPostServer(
                 mainWindow->toast,
                 mainWindow->locationManager->queryFromType(DesktopServerType::TOAST_SUMMON),
                 mainWindow));
         },
          "Initializing ToastPostServer for toast summon" },
        {
          [mainWindow](){
            auto timer_server = new TimerServerMonitoring(mainWindow);
            auto screen_server = new ScreenDetectorServer(timer_server);
            mainWindow->servers.emplaceBack(timer_server);

            MouseProcessor* screen_clicker = new MouseProcessor([mainWindow](MouseRecorder* recorder) -> bool {
                return true; // Always process
            },
            [screen_server, mainWindow](MouseRecorder* recorder) -> bool {
                screen_server->process_reset_timer();
                return true;
            });
            screen_clicker->setName("Screen Light Controller");
            mainWindow->mouseManager->register_processor(screen_clicker);
         }, "Initializing Period Timer Server For backend timers"
        }
    };

    for (const auto& session : sessions) {
        auto [functor, name] = session;
        initer->install_tasks(std::make_shared<AutoStepInitTask>(std::move(functor), QString::fromUtf8(name)));
    }
}

void DesktopMainWindowInitHelper::session_of_init_plugins(DesktopMainWindow* mainWindow, AutoStepIniter* initer) {
    const std::pair<std::function<void()>, const char*> sessions[] = {
        { [mainWindow]() {
             DesktopWidgetPluginServer* pluginWidgetServer = new DesktopWidgetPluginServer(
                 mainWindow->locationManager->queryFromType(DesktopServerType::PLUGIN_WIDGET_PLACED),
                 mainWindow);
             mainWindow->servers.emplaceBack(pluginWidgetServer);
             mainWindow->hooks.emplaceBack(new DesktopCardHook(
                 mainWindow->homePage->homeCardManager(),
                 pluginWidgetServer));
             pluginWidgetServer->scanTargetDirent();
         },
          "Setting up DesktopWidgetPluginServer, DesktopCardHook and scanning plugin directory" }
    };
    for (const auto& session : sessions) {
        auto [functor, name] = session;
        initer->install_tasks(std::make_shared<AutoStepInitTask>(std::move(functor), QString::fromUtf8(name)));
    }
}

void DesktopMainWindowInitHelper::session_of_later_init(DesktopMainWindow* mainWindow, AutoStepIniter* initer) {
}
