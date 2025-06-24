#include "appwidget.h"
#include "app_wrapper/applicationwrapper.h"
#include "ui_appwidget.h"
#include <QRegularExpression>

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

void AppWidget::bindApp(ApplicationWrapper* wrapper) {
    app_internal = wrapper;
    if (app_internal) // if it is acceptable
        wrapper->bindAppWidget(this);
}

ApplicationWrapper* AppWidget::get_app() const {
    return this->app_internal;
}

void AppWidget::setIcon(const QPixmap& icon) noexcept {
	if (icon.isNull()) {
		ui->icon_label->clear();
		return;
	}
	ui->icon_label->setPixmap(icon);
    int sz = icon.width() + 10;
    ui->icon_label->setFixedSize(sz, sz);
    icon_size = sz + 10;
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

void AppWidget::setDummy(bool dummy) {
    dummy_state = dummy;
}

QPixmap AppWidget::icon() const {
	return ui->icon_label->pixmap();
}

void AppWidget::setIconSize(int iconSize) {
    icon_size = iconSize;
    ui->icon_label->setFixedSize(iconSize, iconSize);
}

int AppWidget::iconSize() const {
    return icon_size;
}

void AppWidget::showIconOnly(bool st) {
	st ? ui->text_container->hide() : ui->text_container->show();
}

QString AppWidget::app_name() const {
	return ui->label->text();
}

void AppWidget::set_displayed_font(const QFont& f) {
    ui->label->setFont(f);
}

QFont AppWidget::currentFont() const {
    return ui->label->font();
}

void AppWidget::setFontColor(const QColor& color) {
    QString style = ui->label->styleSheet();

    static QRegularExpression re(R"(color\s*:\s*[^;]+;?)");
    if (style.contains(re)) {
        style.replace(re, QString("color: %1;").arg(color.name()));
    } else {
        style.append(QString(" color: %1;").arg(color.name()));
    }

    ui->label->setStyleSheet(style);
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
