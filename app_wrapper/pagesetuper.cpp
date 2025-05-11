#include "pagesetuper.h"
#include "appwidget.h"
#include "desktopmainwindow.h"
#include "downdockwidget.h"
#include <QGridLayout>
#include <QStackedWidget>
#define MAX_WIDTH (4)
#define MAX_HEIGHT (4)
/* create for a page append */
QList<AppWidget*>
PageSetuper::create_one_app_only_page_append(
    QStackedWidget* widget, DesktopMainWindow* mainWindow,
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
	widget->addWidget(page);

	return appsWidgets;
}

void PageSetuper::add_to_dock(
    DownDockWidget* downdock,
    DesktopMainWindow* mainWindow,
    const QList<AppWidget*>& widgets) {
    QList<AppWidget*> copys;
    for (const auto& each : widgets) {
        AppWidget* app = new AppWidget(each->icon().scaled(PageSetuper::APP_ICON_SZ, PageSetuper::APP_ICON_SZ, Qt::KeepAspectRatio, Qt::SmoothTransformation), each->app_name(), downdock);
        app->bindApp(each->get_app());
        app->showIconOnly(true);
        copys << app;
        QObject::connect(app, &AppWidget::postAppStatus, mainWindow, &DesktopMainWindow::handle_app_status);
    }

    downdock->set_dock_apps(copys);
}

/* All mappings are defined, thus add directly is OK */
#include "app_wrapper/applicationwrapper.h"
void PageSetuper::
	create_specified_page(QStackedWidget* widget, QWidget* paged_widget) {
	widget->addWidget(paged_widget);
}

QList<AppWidget*> PageSetuper::create_real_app(DesktopMainWindow* mainWindow) {

	QList<PageSetuper::PageSetupSessionRequest> req;
	ApplicationWrapper* wrapper = nullptr;
#ifdef INCLUDE_PDF_BROWSER_APP
	/* app page of PDF Browser */
	QString pdf_path;
	pdf_path = _EXTERNAPP_INSTALL_DIR "/pdfReader";
	wrapper = new ApplicationWrapper(mainWindow, mainWindow);
	wrapper->set_app_path(pdf_path);
	mainWindow->install_remote_appwrapper(wrapper);
	req.push_back({ ":/icons/sources/pdf_browser.png", "PDF Browser", wrapper });
#endif

#ifdef INCLUDE_WEATHER_APP
	/* app page of the Weather */
	QString weather_app_path;
	weather_app_path = _EXTERNAPP_INSTALL_DIR "/WeatherApp";
	wrapper = new ApplicationWrapper(mainWindow, mainWindow);
	wrapper->set_app_path(weather_app_path);
	mainWindow->install_remote_appwrapper(wrapper);
	req.push_back({ ":/icons/sources/weather_app.png", "Weather App", wrapper });
#endif

#ifdef INCLUDE_CAMERA_APP
	/* app page of the GeneralLocalCamera */
	QString camera_app_path = _EXTERNAPP_INSTALL_DIR "/GeneralLocalCamera";
	wrapper = new ApplicationWrapper(mainWindow, mainWindow);
	wrapper->set_app_path(camera_app_path);
	mainWindow->install_remote_appwrapper(wrapper);
	req.push_back({ ":/icons/sources/camera_app.png", "Camera App", wrapper });
#endif

#ifdef INCLUDE_SYSTEMSTATUS_APP
	/* app page of the SystemState */
	QString system_state_path = _EXTERNAPP_INSTALL_DIR "/SystemState";
	wrapper = new ApplicationWrapper(mainWindow, mainWindow);
	wrapper->set_app_path(system_state_path);
	mainWindow->install_remote_appwrapper(wrapper);
	req.push_back({ ":/icons/sources/system_state.png", "SystemState", wrapper });
#endif

#ifdef INCLUDE_FILERAMBER_APP
	/* app page of the FileRamber */
	QString file_ramber_path = _EXTERNAPP_INSTALL_DIR "/FileRamber";
	wrapper = new ApplicationWrapper(mainWindow, mainWindow);
	wrapper->set_app_path(file_ramber_path);
	mainWindow->install_remote_appwrapper(wrapper);
	req.push_back({ ":/icons/sources/file_ramber.png", "FileRamber", wrapper });
#endif

#ifdef INCLUDE_MEDIAPLAYER_APP
	/* app page of the MediaPlayer */
	QString media_player_path = _EXTERNAPP_INSTALL_DIR "/MediaPlayer";
	wrapper = new ApplicationWrapper(mainWindow, mainWindow);
	wrapper->set_app_path(media_player_path);
	mainWindow->install_remote_appwrapper(wrapper);
	req.push_back({ ":/icons/sources/mediaplayer_app.png", "MediaPlayer", wrapper });
#endif

	return PageSetuper::create_one_app_only_page_append(mainWindow->stackedWidget(), mainWindow, req);
}
