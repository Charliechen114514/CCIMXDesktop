#include "DesktopAboutMainWidget.h"
#include "ui_DesktopAboutMainWidget.h"
#include <QGraphicsDropShadowEffect>
DesktopAboutMainWidget::DesktopAboutMainWidget(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::DesktopAboutMainWidget) {
	ui->setupUi(this);

	/* logo */
	QGraphicsDropShadowEffect* shadow = new QGraphicsDropShadowEffect(ui->logo);
	shadow->setBlurRadius(20);
	shadow->setColor(QColor(0, 0, 0, 150));
	shadow->setOffset(0, 4);
	ui->logo->setGraphicsEffect(shadow);

	/* descriptions */
	ui->description->setWordWrap(true);
}

void DesktopAboutMainWidget::setLogo(const QIcon& icon) {
	ui->logo->setPixmap(icon.pixmap(PIX_SZ, PIX_SZ));
}

void DesktopAboutMainWidget::setVersionString(const QString& version_string) {
	ui->version->setText("version: " + version_string);
}

void DesktopAboutMainWidget::setTitle(const QString& title) {
	ui->title->setText(title);
}

void DesktopAboutMainWidget::setDescriptions(const QString& descriptions) {
	ui->description->setText(descriptions);
}

void DesktopAboutMainWidget::setMoreInfo(const QString& info) {
	ui->info->setText(info);
}

DesktopAboutMainWidget::~DesktopAboutMainWidget() {
	delete ui;
}
