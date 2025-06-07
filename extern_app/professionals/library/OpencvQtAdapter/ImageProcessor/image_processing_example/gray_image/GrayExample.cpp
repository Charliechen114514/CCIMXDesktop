#include "GrayExample.h"
#include "ui_GrayExample.h"

GrayExample::GrayExample(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::GrayExample) {
	ui->setupUi(this);
    connect(ui->image_controller, &ImageProcessingWidget::image_loaded,
            ui->image_displayer, &ImageResultDisplayer::setRawImage);
}

GrayExample::~GrayExample() {
	delete ui;
}
