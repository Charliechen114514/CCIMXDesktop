#include "desktopmainwindow.h"
#include "app_wrapper/applicationwrapper.h"
#include "app_wrapper/pagesetuper.h"
#include "builtin/core/global_clock_src/GlobalClockSources.h"
#include "builtin/core/netability_scanner/NetAbilityScanner.h"
#include "builtin/ui/pagefactory.h"
#include "builtin/window/applauncher/ApplicationLauncherMainWindow.h"
#include "builtin/window/settings_window/SettingsWindow.h"
#include "core/wallpaper/WallPaperEngine.h"
#include "ui/UiTools.h"
#include "ui/appcardwidget.h"
#include "ui/desktoptoast.h"
#include "ui/stackpage_switcher_animation.h"
#include "ui_desktopmainwindow.h"
#include <QMouseEvent>
#include <QTimer>
DesktopMainWindow::DesktopMainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::DesktopMainWindow) {
    ui->setupUi(this);
    post_setupui();
    setup_apps();
}

void DesktopMainWindow::post_setupui() {
	ui->downdock->set_parent_window(this);
	toast = new DesktopToast(this);
    wallpaper_engine = new WallPaperEngine(this);
    appLauncherWindow = new ApplicationLauncherMainWindow(this);
    scanner = new NetAbilityScanner(this);
    clock = new GlobalClockSources(this);
    ui->topsidewidgetbar->installHookedWindow(this);
    settingsWindow = new SettingsWindow(this);
}

DesktopMainWindow::~DesktopMainWindow() {
	delete ui;
}

void DesktopMainWindow::setup_apps() {
	/* Home Page */
	QWidget* homePage = PageFactory::build_home_page(this);
	PageSetuper::create_specified_page(ui->stackedWidget, homePage);

    app_widgets << PageSetuper::create_builtin_apps(this);
    app_widgets << PageSetuper::create_internal_apps(this);
	app_widgets << PageSetuper::create_real_app(this);

    app_widgets << PageSetuper::build_pesudo_page(":/icons/sources/def_icon2.png", 8, this);
	setup_default_dock();
}

void DesktopMainWindow::setup_default_dock() {
	QList<AppWidget*> docks;
    docks << app_widgets[0];
	PageSetuper::add_to_dock(this, docks);
}

void DesktopMainWindow::invoke_appcards_init() {
	/* sequencely invoke the work */
	for (const auto& each_app_cards : std::as_const(this->app_cards)) {
		each_app_cards->invoke_preLaunch_work();
	}
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

void DesktopMainWindow::mousePressEvent(QMouseEvent* event) {
	records.press = event->pos();
    event->accept();
}

void DesktopMainWindow::mouseReleaseEvent(QMouseEvent* event) {
	records.release = event->pos();
    const QPoint diff = records.press - records.release;

    if (qAbs(diff.x()) < 100 || diff.manhattanLength() < 120) {
        event->ignore();
        return;
    }

    diff.x() < 0 ? to_next_page() : to_prev_page();
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
