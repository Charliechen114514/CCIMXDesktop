#include "MainShowWidget.h"

#include "ui_MainShowWidget.h"

MainShowWidget::MainShowWidget(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::MainShowWidget) {
	ui->setupUi(this);
}

MainShowWidget::~MainShowWidget() {
	delete ui;
}

void MainShowWidget::show_pinger() {
	ui->tabWidget->setCurrentIndex(1);
}

void MainShowWidget::show_scanner() {
	ui->tabWidget->setCurrentIndex(2);
}

void MainShowWidget::show_interfaces() {
	ui->tabWidget->setCurrentIndex(0);
}
