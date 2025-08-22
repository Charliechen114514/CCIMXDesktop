#include "desktopmainwindow.h"
#include "DesktopMainWindowInitHelper.h"
#include "app_wrapper/applicationwrapper.h"
#include "app_wrapper/pagesetuper.h"
#include "builtin/core/global_clock_src/GlobalClockSources.h"
#include "builtin/core/netability_scanner/NetAbilityScanner.h"
#include "builtin/page/homepage.h"
#include "builtin/ui/pagefactory.h"
#include "builtin/window/applauncher/ApplicationLauncherMainWindow.h"
#include "builtin/window/settings_window/SettingsWindow.h"
#include "core/desktop_dirent_manager/DesktopDirentLocationManager.h"
#include "core/loggers/CCIMXDesktopLoggerCenter.h"
#include "core/loggers/ConsoleLogger.h"
#include "core/loggers/DesktopLoggerConvinients.h"
#include "core/users/DesktopUserInfo.h"
#include "core/wallpaper/WallPaperEngine.h"
#include "desktop_settings.h"
#include "library/qt_relative/mouse_press_manager/MouseManager.h"
#include "ui/UiTools.h"
#include "ui/appcardwidget.h"
#include "ui/desktoptoast.h"
#include "ui/stackpage_switcher_animation.h"
#include "ui_desktopmainwindow.h"
#include <QMouseEvent>
#include <QTimer>
void DesktopMainWindow::initLogger() {
    auto& logger_center = CCIMXDesktopLoggerCenter::global_instance();
    logger_center.registerBackend(new ConsoleLogger(ConsoleLogger::ConsoleFormatStyle::LoguruLike));
    Logger::postInfo("ConsoleLogger is Ready!");
}

DesktopUserInfo* DesktopMainWindow::get_user_info() {
    return user_info;
}

DesktopMainWindow::DesktopMainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::DesktopMainWindow) {
    initLogger();
}

void DesktopMainWindow::setup_static_ui() {
    ui->setupUi(this);
}

DesktopMainWindow::~DesktopMainWindow() {
	delete ui;
}

void DesktopMainWindow::init(CCIMX_DesktopSplashWindow* splash) {
    DesktopMainWindowInitHelper::run_init_session(this, splash);
}

void DesktopMainWindow::setup_default_dock() {
	QList<AppWidget*> docks;
    if(!app_widgets.empty())
        docks << app_widgets[0];
    else
        qWarning() << "No app_widget found in app_widgets, so dock widget will place nothing else";
	PageSetuper::add_to_dock(this, docks);
}

void DesktopMainWindow::invoke_appcards_init() {
	/* sequencely invoke the work */
    showToast("AppCards Are Initing...");
	for (const auto& each_app_cards : std::as_const(this->app_cards)) {
		each_app_cards->invoke_preLaunch_work();
	}
    showToast("AppCards Init Finished!");
}

QWidget* DesktopMainWindow::centralWidget() {
    return ui->centralwidget;
}

void DesktopMainWindow::handle_app_status(AppWidget::AppStatus status) {
	switch (status) {
	case AppWidget::AppStatus::AppNonExsits:
		showToast("App is Not binded! bind the app first!");
		break;
	case AppWidget::AppStatus::AppOk: {
		AppWidget* w = dynamic_cast<AppWidget*>(sender());
		ui->downdock->on_app_dispatched(w);
		qDebug() << "hooked app to the downdock:" << w->app_name();
	} break;
	default:
		break;
	}
}

void DesktopMainWindow::open_settings_window() {
    UiTools::openIfUnvisible(settingsWindow, "Settings Window");
}

void DesktopMainWindow::open_launch_window() {
    UiTools::openIfUnvisible(appLauncherWindow, "AppLaunchWindow");
}

void DesktopMainWindow::install_for_new_dynamicpage(AppWidget* appWidgets) {

    const int cnt = ui->stackedWidget->count();
    QWidget* dynamic_page = nullptr;
    for (int i = 0; i < cnt; i++) {
        QWidget* page = ui->stackedWidget->widget(i);
        if (page->objectName() == "dynamic_page_for_launch") {
            dynamic_page = page;
        }
    }

    if (!dynamic_page) {
        // create one page
        PageSetuper::create_new_page_with_appWidget({ appWidgets }, this, "dynamic_page_for_launch");
    } else {
        QGridLayout* layout = dynamic_cast<QGridLayout*>(dynamic_page->layout());
        UiTools::addWidgetToGridTail(layout, appWidgets, PageSetuper::MAX_HEIGHT);
    }
}

void DesktopMainWindow::process_set_appwidgets_config(const AppWidgetsSettingsInfoPack& info) {
    for (auto each : std::as_const(app_widgets)) {
        each->setFontColor(info.fontColor);
        each->setFont(info.font);
        each->setIconSize(info.iconSize);
    }
}

void DesktopMainWindow::process_wallpaper_settings(BaseWallPaperSettings* settings) {
    switch (settings->get_type()) {
    case BaseWallPaperSettings::Type::FIXED: {
        FixedTypeWallPaperSettings* fixed = dynamic_cast<FixedTypeWallPaperSettings*>(settings);
        wallpaper_engine->set_mode(fixed->mode);
        wallpaper_engine->set_showing_pictures(fixed->map);
    } break;
    case BaseWallPaperSettings::Type::FLOW_LIKE: {
        FlowTypeTypeWallPaperSettings* flow = dynamic_cast<FlowTypeTypeWallPaperSettings*>(settings);
        wallpaper_engine->set_animation_duration_second(flow->animation_speed);
        wallpaper_engine->set_image_list(flow->images);
        wallpaper_engine->set_switch_interval(flow->switch_interval);
        wallpaper_engine->set_mode(flow->mode);
        wallpaper_engine->set_easingcurve(flow->curve);
    } break;
    }
}

QStackedWidget* DesktopMainWindow::stackedWidget() const {
	return ui->stackedWidget;
}

TopSideBarWidget* DesktopMainWindow::topSideBar() const {
    return ui->topsidewidgetbar;
}

void DesktopMainWindow::post_show() {
    QTimer::singleShot(0, this, [this]() {
        invoke_appcards_init();
    });
}

void DesktopMainWindow::showToast(const QString& message) {
	toast->set_message(message);
}

DownDockWidget* DesktopMainWindow::downDockWidget() const {
	return ui->downdock;
}

void DesktopMainWindow::back_home_page()
{
    StackpageSwitcherAnimation::AnimationInfo info;
    info.new_index = 0;
    info.toLeft = true;
    StackpageSwitcherAnimation::process_animations(ui->stackedWidget, &info);
}

void DesktopMainWindow::mousePressEvent(QMouseEvent* event) {
    mouseManager->install_mousepoint(
        event->pos(),
        MouseManager::PointType::Press);
    event->accept();
}

void DesktopMainWindow::mouseReleaseEvent(QMouseEvent* event) {
    mouseManager->install_mousepoint(
        event->pos(),
        MouseManager::PointType::Release);

    if (!mouseManager->run_processor()) {
        event->ignore();
        return;
    }
    qDebug() << "Ok, handled!";
    event->accept();
}

void DesktopMainWindow::to_next_page() {
	int currentIndex = ui->stackedWidget->currentIndex();
	if (currentIndex <= 0) {
		return;
	}
	StackpageSwitcherAnimation::AnimationInfo info;
	info.new_index = currentIndex - 1;
	info.toLeft = false;
	StackpageSwitcherAnimation::process_animations(ui->stackedWidget, &info);
}

void DesktopMainWindow::to_prev_page() {
	int currentIndex = ui->stackedWidget->currentIndex();
	if (currentIndex >= ui->stackedWidget->count() - 1) {
		return;
	}
	StackpageSwitcherAnimation::AnimationInfo info;
	info.new_index = currentIndex + 1;
	info.toLeft = true;
	StackpageSwitcherAnimation::process_animations(ui->stackedWidget, &info);
}

void DesktopMainWindow::resizeEvent(QResizeEvent* event) {
	QMainWindow::resizeEvent(event);
	/* makeups the full screen */
    wallpaper_engine->process_resize(this);
}
