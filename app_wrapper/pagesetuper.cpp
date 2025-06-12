#include "pagesetuper.h"
#include "appwidget.h"
#include "desktopmainwindow.h"
#include "downdockwidget.h"
#include <QGridLayout>
#include <QStackedWidget>

/* create for a page append */
QList<AppWidget*>
PageSetuper::create_one_app_only_page_append(
    DesktopMainWindow* mainWindow,
    const QList<PageSetupSessionRequest>& sessionRequest) {
    QList<AppWidget*> appsWidgets;
    QWidget* page = new QWidget(mainWindow);
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

	while (j < MAX_WIDTH + MAX_HEIGHT) {
		/* this is a temp dummy apps */
		gridLayout->addWidget(new QWidget(mainWindow), j / MAX_WIDTH, j % MAX_HEIGHT);
		j++;
	}

	page->setLayout(gridLayout);
	mainWindow->stackedWidget()->addWidget(page);

	return appsWidgets;
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
	QList<PageSetuper::PageSetupSessionRequest> req;
	for (int i = 0; i < how_many; i++) {
		req.push_back({ pixpath, QString::number(i), nullptr });
	}

	return PageSetuper::create_one_app_only_page_append(mainWindow, req);
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
	return PageSetuper::create_one_app_only_page_append(mainWindow, req);
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

	return PageSetuper::create_one_app_only_page_append(mainWindow, req);
}
