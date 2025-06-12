#include "HistDrawer.h"
#include "CVImage.h"
#include "HistCreator.h"
#include "QtAdaptTools.h"
#include "ui_HistDrawer.h"
HistDrawer::HistDrawer(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::HistDrawer) {
	ui->setupUi(this);
    connect(ui->image_controller, &ImageProcessingWidget::image_loaded,
            ui->image_displayer, &ImageResultDisplayer::setRawImage);
    connect(ui->image_controller, &ImageProcessingWidget::request_processing,
            this, &HistDrawer::process_image_session);
    ui->image_controller->process_direct_load(":/example_image/lena.jpg");
}

HistDrawer::~HistDrawer() {
	delete ui;
}

void HistDrawer::process_image_session() {
    QImage image = ui->image_controller->image();
    if (image.isNull()) {
        return;
    }
    CVImage cvImage = QtAdaptTools::fromRGBQImage(image);
    CVImage blank;
    HistCreator::filled_hist(blank, cvImage);
    QImage new_image = QtAdaptTools::toDisplayableImage(blank);
    ui->image_displayer->setProcessedImage(new_image);
}
