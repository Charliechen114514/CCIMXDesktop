#include "SimpleDrawerWidget.h"
#include "SaveWindow.h"
#include "core/SimpleDrawingScene.h"
#include "ui_SimpleDrawerWidget.h"
SimpleDrawerWidget::SimpleDrawerWidget(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::SimpleDrawerWidget) {
	ui->setupUi(this);
	scene = new SimpleDrawingScene(this);

	ui->display_view->setScene(scene);
	setMouseTracking(true);
	ui->display_view->setDragMode(QGraphicsView::NoDrag);
}

SimpleDrawerWidget::~SimpleDrawerWidget() {
	delete ui;
}
