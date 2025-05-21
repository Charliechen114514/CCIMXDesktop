#include "appwidget.h"
#include "app_wrapper/applicationwrapper.h"
#include "ui_appwidget.h"

/* oh, kotlin do a good job then :) */
AppWidget::AppWidget(const QPixmap& icon, const QString& name, QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::AppWidget) {
    ui->setupUi(this);
    setAttribute(Qt::WA_TranslucentBackground);

	ui->label->setAlignment(Qt::AlignCenter);
	ui->icon_label->setAlignment(Qt::AlignCenter);
	layout()->setAlignment(Qt::AlignCenter);

	ui->label->setScaledContents(true);
	setAppName(name);
	setIcon(icon);

	ui->icon_label->installEventFilter(this);

	/* App Icon Style */
	ui->icon_label->setStyleSheet(
		"QLabel {"
		"background: qlineargradient(spread:pad, "
		"x1:0, y1:0, x2:1, y2:1, "
		"stop:0 rgba(150, 150, 150, 100), "
		"stop:1 rgba(130, 130, 130, 255));"
		"border-radius: 15px;"
		"border: 2px solid rgba(0, 0, 0, 100);"
		"}");
}

void AppWidget::setIcon(const QPixmap& icon) noexcept {
	if (icon.isNull()) {
		ui->icon_label->clear();
		return;
	}
	ui->icon_label->setPixmap(icon);
	int sz = icon.width();
	ui->icon_label->setFixedSize(sz + 10, sz + 10);
}

void AppWidget::setAppName(const QString& name) noexcept {
	if (name.isEmpty()) {
		ui->label->clear();
		return;
	}

	ui->label->setText(name);
	ui->text_container->setFixedHeight(
		ui->label->fontMetrics().height() + 10);
}

QPixmap AppWidget::icon() const {
	return ui->icon_label->pixmap();
}

void AppWidget::showIconOnly(bool st) {
	st ? ui->text_container->hide() : ui->text_container->show();
}

QString AppWidget::app_name() const {
	return ui->label->text();
}

AppWidget::~AppWidget() {
	delete ui;
}

bool AppWidget::eventFilter(QObject* watched, QEvent* event) {
	if (watched == ui->icon_label) {
		if (event->type() == QEvent::MouseButtonPress) {
			do_daptch();
			return true;
		}
	}
	return QWidget::eventFilter(watched, event);
}

void AppWidget::do_daptch() {
	if (dummy_state) {
		return; // dummy apps don't do anything
	}
	if (!app_internal) {
		qDebug() << "app is not binded, check the path";
		emit postAppStatus(AppStatus::AppNonExsits);
		return;
	} else {
		qDebug() << "about depatch the app " << app_internal->get_app_path();
		app_internal->depatch_app();
		emit postAppStatus(AppStatus::AppOk);
	}
}
