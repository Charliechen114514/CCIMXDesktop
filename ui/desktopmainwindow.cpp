#include "desktopmainwindow.h"
#include "app_wrapper/applicationwrapper.h"
#include "app_wrapper/pagesetuper.h"
#include "builtin/ui/pagefactory.h"
#include "core/coretools.h"
#include "desktop_settings.h"
#include "ui/appcardwidget.h"
#include "ui/desktoptoast.h"
#include "ui/stackpage_switcher_animation.h"
#include "ui/wallpaperanimationhandler.h"
#include "ui_desktopmainwindow.h"
#include <QGridLayout>
#include <QLabel>
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
	setup_bg_image();
}

void DesktopMainWindow::setup_bg_image() {
	wallPaperGroup.wallpaperLabel = new QLabel(this);
	wallPaperGroup.wallpaperLabel->setScaledContents(true);
	wallPaperGroup.wallpaperLabel->lower();
	wallPaperGroup.wallpaperLabel->setGeometry(0, 0, width(), height());

	wallPaperGroup.bufferpaperLabel = new QLabel(this);
	wallPaperGroup.bufferpaperLabel->setScaledContents(true);
	wallPaperGroup.bufferpaperLabel->lower();
	wallPaperGroup.bufferpaperLabel->setGeometry(0, 0, width(), height());
	wallPaperGroup.bufferpaperLabel->hide();
	wallPaperGroup.shoule_be_lower = centralWidget();
	/* now collect all the images */
	image_lists << CoreTools::enumeratefiles(DEFAULT_DESKTOP_PLACES, { "*.png" });
	if (!image_lists.isEmpty()) {
		wallPaperGroup.wallpaperLabel->setPixmap(QPixmap(image_lists[0]));
	}
	wallPaperGroup.invoke_switch_timer = new QTimer(this);
	wallPaperGroup.invoke_switch_timer->setInterval(switch_bg_time);
	connect(wallPaperGroup.invoke_switch_timer, &QTimer::timeout,
			this, &DesktopMainWindow::invoke_switch_bgpage);
	wallPaperGroup.invoke_switch_timer->start();
}

DesktopMainWindow::~DesktopMainWindow() {
	delete ui;
}

void DesktopMainWindow::invoke_switch_bgpage() {
	/* switch the background page */
	WallPaperAnimationHandler::ImagePoolEngine engine;
	engine.image_list = &this->image_lists;
	WallPaperAnimationHandler::process_switch(this->wallPaperGroup, engine);
}

void DesktopMainWindow::setup_apps() {
	/* Home Page */
	QWidget* homePage = PageFactory::build_home_page(this);
	PageSetuper::create_specified_page(ui->stackedWidget, homePage);

	app_widgets << PageSetuper::create_real_app(this);
	app_widgets << PageSetuper::create_builtin_apps(this);

	app_widgets << PageSetuper::build_pesudo_page(":/icons/sources/def_icon.png", 8, this);
	app_widgets << PageSetuper::build_pesudo_page(":/icons/sources/def_icon2.png", 8, this);

	setup_default_dock();
}

void DesktopMainWindow::setup_default_dock() {
	QList<AppWidget*> docks;
	docks << app_widgets[0] << app_widgets[6];
	PageSetuper::add_to_dock(this, docks);
}

void DesktopMainWindow::invoke_appcards_init() {
	/* sequencely invoke the work */
	for (const auto& each_app_cards : std::as_const(this->app_cards)) {
		each_app_cards->invoke_preLaunch_work();
	}
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

QStackedWidget* DesktopMainWindow::stackedWidget() const {
	return ui->stackedWidget;
}

void DesktopMainWindow::post_show() {
	connect(this, &DesktopMainWindow::deptach_app_cards_init,
			this, &DesktopMainWindow::invoke_appcards_init);

	emit deptach_app_cards_init();
}

void DesktopMainWindow::showToast(const QString& message) {
	toast->set_message(message);
}

DownDockWidget* DesktopMainWindow::downDockWidget() const {
	return ui->downdock;
}

void DesktopMainWindow::mousePressEvent(QMouseEvent* event) {
	records.press = event->pos();
}

void DesktopMainWindow::mouseReleaseEvent(QMouseEvent* event) {
	records.release = event->pos();
	int move_range = records.press.x() - records.release.x();

	if (qAbs(move_range) < 100) {
		return;
	}

	move_range < 0 ? to_next_page() : to_prev_page();
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
	if (wallPaperGroup.wallpaperLabel) {
		wallPaperGroup.wallpaperLabel->setGeometry(0, 0, width(), height());
	}

	if (wallPaperGroup.bufferpaperLabel) {
		wallPaperGroup.bufferpaperLabel->setGeometry(0, 0, width(), height());
	}
}
