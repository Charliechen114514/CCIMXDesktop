#include "StaticStatusBarIconWidget.h"
#include "ui_StaticStatusBarIconWidget.h"

StaticStatusBarIconWidget::StaticStatusBarIconWidget(QString name, QWidget* parent)
    : StatusBarIconWidget(name, parent)
    , ui(new Ui::StaticStatusBarIconWidget) {
	ui->setupUi(this);
}

StaticStatusBarIconWidget::~StaticStatusBarIconWidget() {
	delete ui;
}

QPixmap StaticStatusBarIconWidget::icon() {
    return ui->iconlabel->pixmap();
}

void StaticStatusBarIconWidget::setIcon(const QPixmap& map) {
    ui->iconlabel->setPixmap(map.scaled(ui->iconlabel->height(), ui->iconlabel->height(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

void StaticStatusBarIconWidget::adjustSelfHeight(int height) {
    setFixedHeight(height);
}
