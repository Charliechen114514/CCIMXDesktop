#include "GrayExample.h"
#include "CVImage.h"
#include "GrayProcessor.h"
#include "QtAdaptTools.h"
#include "ui_GrayExample.h"
GrayExample::GrayExample(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::GrayExample) {
	ui->setupUi(this);
    connect(ui->image_controller, &ImageProcessingWidget::image_loaded,
            ui->image_displayer, &ImageResultDisplayer::setRawImage);
    connect(ui->image_controller, &ImageProcessingWidget::request_processing,
            this, &GrayExample::process_image_session);
}

void GrayExample::process_image_session() {
    QImage image = ui->image_controller->image();
    CVImage cvImage = QtAdaptTools::fromRGBQImage(image);
    GrayProcessor processor;
    processor.process(cvImage);
    QImage new_image = QtAdaptTools::toDisplayableImage(cvImage);
    ui->image_displayer->setProcessedImage(new_image);
}

GrayExample::~GrayExample() {
	delete ui;
}
