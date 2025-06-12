#include "FaceDetectionExample.h"
#include "CVImage.h"
#include "FaceDetector.h"
#include "QtAdaptTools.h"
#include "ui_FaceDetectionExample.h"
#include <QMessageBox>
FaceDetectionExample::FaceDetectionExample(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::FaceDetectionExample) {
	ui->setupUi(this);
    connect(ui->image_controller, &ImageProcessingWidget::image_loaded,
            ui->image_displayer, &ImageResultDisplayer::setRawImage);
    connect(ui->image_controller, &ImageProcessingWidget::request_processing,
            this, &FaceDetectionExample::process_image_session);
    ui->image_controller->process_direct_load(":/example_image/lena.jpg");
}

FaceDetectionExample::~FaceDetectionExample() {
	delete ui;
}

void FaceDetectionExample::process_image_session() {
    QImage image = ui->image_controller->image();
    if (image.isNull()) {
        return;
    }
    CVImage cvImage = QtAdaptTools::fromRGBQImage(image);
    CVImage blank;
    try {
        FaceDetector::detectFaces(blank, cvImage);
    } catch (const std::runtime_error& e) {
        QMessageBox::critical(this, "Error", QString("Error occurs: ") + e.what());
        return;
    }

    QImage new_image
        = QtAdaptTools::toDisplayableImage(blank);
    ui->image_displayer->setProcessedImage(new_image);
}
