#include "downdockwidget.h"
#include "app_wrapper/pagesetuper.h"
#include "appwidget.h"
#include "ui/desktopmainwindow.h"
#include "ui_downdockwidget.h"
#include <QGraphicsDropShadowEffect>
#include <QHBoxLayout>

namespace {
AppWidget* mirror_app(const AppWidget* app, DesktopMainWindow* w) {
	AppWidget* copy = new AppWidget(
		app->icon().scaled(PageSetuper::APP_ICON_SZ,
						   PageSetuper::APP_ICON_SZ,
						   Qt::KeepAspectRatio,
						   Qt::SmoothTransformation),
		app->app_name(), w->downDockWidget());
	copy->bindApp(app->get_app());
	copy->showIconOnly(true);
	QObject::connect(copy, &AppWidget::postAppStatus, w, &DesktopMainWindow::handle_app_status);
	return copy;
}
}

DownDockWidget::DownDockWidget(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::DownDockWidget) {
    ui->setupUi(this);
    setAttribute(Qt::WA_StyledBackground, true);
    setAutoFillBackground(true);
    setStyleSheet(
        "DownDockWidget {"
        "    background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, "
        "        stop:0 rgba(40, 40, 40, 0.8), stop:1 rgba(100, 100, 100, 0.8));"
        "    border-radius: 12px;"
        "    border: 1px solid rgba(100, 100, 100, 0.5);"
        "    padding: 16px;"
        "}");
}

void DownDockWidget::set_dock_apps(const QList<AppWidget*>& apps) {
	for (const auto& app : apps) {
		on_app_dispatched(app);
	}
}

void DownDockWidget::replace_docks() {
	std::sort(dock_apps.begin(), dock_apps.end(), [this](AppWidget* a, AppWidget* b) {
		return app_usage_count.value(a, 0) > app_usage_count.value(b, 0);
	});

	QList<AppWidget*> top_apps = dock_apps.mid(0, DOCK_MAX_APP_CNT);
	QLayout* layout = this->layout();
	if (layout) {
		QLayoutItem* item;
		layout->takeAt(0);
	}

	for (AppWidget* app : std::as_const(top_apps)) {
		layout->addWidget(app);
	}
}

DownDockWidget::~DownDockWidget() {
	delete ui;
}

void DownDockWidget::on_app_dispatched(const AppWidget* app) {
	AppWidget* internal_mirror = nullptr;
	auto it = std::find_if(dock_apps.cbegin(), dock_apps.cend(),
						   [&](AppWidget* each) {
							   return each->get_app()->get_app_path() == app->get_app()->get_app_path();
						   });

	if (it != dock_apps.cend()) {
		internal_mirror = *it;
	}

	if (!dock_apps.contains(internal_mirror)) {
		AppWidget* possible_copy = mirror_app(app, parent_window);
		dock_apps.append(possible_copy);
		internal_mirror = possible_copy;
	}

	app_usage_count[internal_mirror] += 1;
	replace_docks();
}
