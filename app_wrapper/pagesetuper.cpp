#include "pagesetuper.h"
#include "appwidget.h"
#include "desktop_settings.h"
#include "desktopmainwindow.h"
#include "downdockwidget.h"
#include "ui/UiTools.h"
#include <QGridLayout>
#include <QStackedWidget>
/* create for a page append */
QList<AppWidget*>
PageSetuper::create_one_app_only_page_append(
    DesktopMainWindow* mainWindow,
    const QList<PageSetupSessionRequest>& sessionRequest,
    const QString& pageName) {
    QList<AppWidget*> appsWidgets;
    QWidget* page = new QWidget(mainWindow);
    page->setObjectName(pageName);
    QGridLayout* gridLayout = new QGridLayout(page);
    gridLayout->setSpacing(20);
    gridLayout->setContentsMargins(30, 30, 30, 30);
    int j = 0;
    for (const auto& session : sessionRequest) {
        AppWidget* app = new AppWidget(
            QPixmap(session.pixmap_addr).scaled(PageSetuper::APP_ICON_SZ, PageSetuper::APP_ICON_SZ, Qt::KeepAspectRatio, Qt::SmoothTransformation),
            session.app_name, mainWindow);

		app->bindApp(session.app);
		appsWidgets << app;
		QObject::connect(app, &AppWidget::postAppStatus, mainWindow, &DesktopMainWindow::handle_app_status);
		gridLayout->addWidget(app, j / MAX_WIDTH, j % MAX_HEIGHT);
		j++;
	}

	page->setLayout(gridLayout);
	mainWindow->stackedWidget()->addWidget(page);

	return appsWidgets;
}

void PageSetuper::create_new_page_with_appWidget(
    QList<AppWidget*> appWidgets,
    DesktopMainWindow* mainWindow, const QString& name) {
    QWidget* page = new QWidget(mainWindow);
    page->setObjectName(name);
    QGridLayout* gridLayout = new QGridLayout(page);
    gridLayout->setSpacing(20);
    gridLayout->setContentsMargins(30, 30, 30, 30);
    int j = 0;
    for (const auto& session : appWidgets) {
        gridLayout->addWidget(session, j / MAX_WIDTH, j % MAX_HEIGHT);
        j++;
    }
    page->setLayout(gridLayout);
    mainWindow->stackedWidget()->addWidget(page);
}

void PageSetuper::add_to_dock(
    DesktopMainWindow* mainWindow,
    const QList<AppWidget*>& widgets) {
    mainWindow->downDockWidget()->set_dock_apps(widgets);
}

/* All mappings are defined, thus add directly is OK */
#include "app_wrapper/applicationwrapper.h"
void PageSetuper::
    create_specified_page(QStackedWidget* widget, QWidget* paged_widget) {
	widget->addWidget(paged_widget);
}

namespace {
PageSetuper::PageSetupSessionRequest make_up_request(
    const QString& app_path,
    const QString& icon_path,
    const QString& name, DesktopMainWindow* mainWindow) {
    ApplicationWrapper* wrapper = new ApplicationWrapper(mainWindow, mainWindow);
    wrapper->set_app_path(app_path);
    mainWindow->install_remote_appwrapper(wrapper);
    return { icon_path, name, wrapper };
}
}

QList<AppWidget*> PageSetuper::build_pesudo_page(
    const QString& pixpath, int how_many, DesktopMainWindow* mainWindow) {
    static int pesudo_page_index = 0;

    QList<PageSetuper::PageSetupSessionRequest> req;
	for (int i = 0; i < how_many; i++) {
		req.push_back({ pixpath, QString::number(i), nullptr });
	}

    return PageSetuper::create_one_app_only_page_append(
        mainWindow, req, "pesudo_page" + QString::number(pesudo_page_index));
}

QList<AppWidget*> PageSetuper::create_real_app(DesktopMainWindow* mainWindow) {

	QList<PageSetuper::PageSetupSessionRequest> req;
#ifdef INCLUDE_PDF_BROWSER_APP
	req.push_back(make_up_request(
        _EXTERNAPP_INSTALL_DIR "/pdfReader",
        ":/icons/sources/pdf_browser.png",
        "PDF Browser",
        mainWindow));
#endif

#ifdef INCLUDE_WEATHER_APP
	req.push_back(make_up_request(
        _EXTERNAPP_INSTALL_DIR "/WeatherApp",
        ":/icons/sources/weather_app.png",
        "Weather App",
        mainWindow));
#endif

#ifdef INCLUDE_CAMERA_APP
	req.push_back(make_up_request(
        _EXTERNAPP_INSTALL_DIR "/GeneralLocalCamera",
        ":/icons/sources/camera_app.png",
        "Camera App",
        mainWindow));
#endif

#ifdef INCLUDE_SYSTEMSTATUS_APP
	req.push_back(make_up_request(
        _EXTERNAPP_INSTALL_DIR "/SystemState",
        ":/icons/sources/system_state.png",
        "SystemState",
        mainWindow));
#endif

#ifdef INCLUDE_FILERAMBER_APP
	req.push_back(make_up_request(
        _EXTERNAPP_INSTALL_DIR "/FileRamber",
        ":/icons/sources/file_ramber.png",
        "FileRamber",
        mainWindow));
#endif

#ifdef INCLUDE_MEDIAPLAYER_APP
	req.push_back(make_up_request(
        _EXTERNAPP_INSTALL_DIR "/MediaPlayer",
        ":/icons/sources/mediaplayer_app.png",
        "MediaPlayer",
        mainWindow));
#endif

#ifdef INCLUDE_LED_APP
	req.push_back(make_up_request(
        _EXTERNAPP_INSTALL_DIR "/LightController",
        ":/icons/sources/ledcontrol_app.png",
        "LED Controller",
        mainWindow));
#endif

#ifdef INCLUDE_ENV_APP
	req.push_back(make_up_request(
        _EXTERNAPP_INSTALL_DIR "/Environment",
        ":/icons/sources/env_app.png",
        "Environment",
        mainWindow));
#endif

#ifdef INCLUDE_SPORT_APP
	req.push_back(make_up_request(
        _EXTERNAPP_INSTALL_DIR "/SportsHealth",
        ":/icons/sources/sports_health_app.png",
        "SportsHealth",
        mainWindow));
#endif

#ifdef INCLUDE_NETHELPER_APP
	req.push_back(make_up_request(
        _EXTERNAPP_INSTALL_DIR "/CCNetHelper",
        ":/icons/sources/network-helper.png",
        "CCNetHelper",
        mainWindow));
#endif

#ifdef INCLUDE_EASYNOTE_APP
	req.push_back(make_up_request(
        _EXTERNAPP_INSTALL_DIR "/EasyNotes",
        ":/icons/sources/EasyNote.png",
        "EasyNotes",
        mainWindow));
#endif

#ifdef INCLUDE_DINO_GAME
	req.push_back(make_up_request(
        _EXTERNAPP_INSTALL_DIR "/CCIMX_DinoGame",
        ":/icons/sources/dino_frame1.png",
        "CCIMX_DinoGame",
        mainWindow));
#endif

#ifdef INCLUDE_IMAGE_PROCESSOR
    req.push_back(make_up_request(
        _EXTERNAPP_INSTALL_DIR "/ImageProcessor",
        ":/icons/sources/image_processor.png",
        "ImageProcessor",
        mainWindow));
#endif
    req.push_back(make_up_request(
        _EXTERNAPP_INSTALL_DIR "/CCIMXCommunicate",
        ":/icons/sources/communicator.png",
        "CCommunicator",
        mainWindow));
#ifdef INCLUDE_CCOMMUNICATOR_APP

#endif
    return PageSetuper::create_one_app_only_page_append(mainWindow, req, "realapp_page");
}

QList<AppWidget*> PageSetuper::create_builtin_apps(DesktopMainWindow* mainWindow) {
	QList<PageSetuper::PageSetupSessionRequest> req;

	/* abouts */
	req.push_back(make_up_request(
        _EXTERNAPP_INSTALL_DIR "/DesktopAbout",
        ":/icons/sources/desktop_about.png",
        "DesktopAbout",
        mainWindow));

	/* simple drawer */
	req.push_back(make_up_request(
        _EXTERNAPP_INSTALL_DIR "/SimpleDrawer",
        ":/icons/sources/simple_drawer.png",
        "SimpleDrawer",
        mainWindow));

    req.push_back(make_up_request(
        _EXTERNAPP_INSTALL_DIR "/CCIMXNoter",
        ":/icons/sources/notepad.png",
        "CCIMXNoter",
        mainWindow));

	req.push_back(make_up_request(
        _EXTERNAPP_INSTALL_DIR "/ImageWalker",
        ":/icons/sources/image_walker.png",
        "ImageWalker",
        mainWindow));

	req.push_back(make_up_request(
        _EXTERNAPP_INSTALL_DIR "/Caculator",
        ":/icons/sources/caculator.png",
        "Caculator",
        mainWindow));

    req.push_back(make_up_request(
        _EXTERNAPP_INSTALL_DIR "/CCCalendar",
        ":/icons/sources/calendar.png",
        "Calendar",
        mainWindow));

    req.push_back(make_up_request(_EXTERNAPP_INSTALL_DIR"/AlarmyClock",
                                  ":/icons/sources/alarmy_clock.png",
                                  "Clock",mainWindow));

    return PageSetuper::create_one_app_only_page_append(
        mainWindow, req, "builtin_page");
}

namespace {
QWidget* query_target(const QString& name, QStackedWidget* stacked_widget) {
    QWidget* target = nullptr;
    const int count = stacked_widget->count();
    for (int i = 0; i < count; i++) {
        QWidget* iterate = stacked_widget->widget(i);
        if (iterate->objectName() == name) {
            target = iterate;
            break;
        }
    }
    return target;
}
}

#include "builtin/window/applauncher/fakeapps/AppLauncherApp.h"
#include "builtin/window/settings_window/fake_app_entry/SettingsApp.h"
QList<AppWidget*> PageSetuper::create_internal_apps(DesktopMainWindow* mainWindow) {
    /* append to the page of builtins */
    QWidget* builtin_page = query_target("builtin_page", mainWindow->stackedWidget());
    if (!builtin_page) {
        qCritical() << "Can not find the builtin page! Settings will not be created!";
        return {};
    }
    SettingsApp* settings_app = new SettingsApp(mainWindow);
    QObject::connect(settings_app, &SettingsApp::indicate_open_settings_window,
                     mainWindow, &DesktopMainWindow::open_settings_window);
    QObject::connect(settings_app, &AppWidget::postAppStatus,
                     mainWindow, &DesktopMainWindow::handle_app_status);
    QGridLayout* layout = dynamic_cast<QGridLayout*>(builtin_page->layout());
    UiTools::addWidgetToGridTail(layout, settings_app, MAX_HEIGHT);

    AppLauncherApp* launch_app = new AppLauncherApp(mainWindow);
    QObject::connect(launch_app, &AppLauncherApp::indicate_open_launch_window,
                     mainWindow, &DesktopMainWindow::open_launch_window);
    QObject::connect(launch_app, &AppWidget::postAppStatus,
                     mainWindow, &DesktopMainWindow::handle_app_status);
    UiTools::addWidgetToGridTail(layout, launch_app, MAX_HEIGHT);
    return { launch_app, settings_app };
}
