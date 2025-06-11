#include "CannyExample.h"
#include "CVImage.h"
#include "CannyProcessor.h"
#include "QtAdaptTools.h"
#include "ui_CannyExample.h"
CannyExample::CannyExample(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::CannyExample) {
	ui->setupUi(this);
    connect(ui->image_controller, &ImageProcessingWidget::image_loaded,
            ui->image_displayer, &ImageResultDisplayer::setRawImage);
    connect(ui->image_controller, &ImageProcessingWidget::request_processing,
            this, &CannyExample::process_image_session);
    ui->image_controller->process_direct_load(":/example_image/lena.jpg");
    ui->lowThredSpinbox->setValue(Processor::Canny::LOW);
    ui->highThreadSpinbox->setValue(Processor::Canny::HIGH);
    connect(ui->lowThredSpinbox, &QSpinBox::valueChanged,
            this, &CannyExample::process_image_session);

    connect(ui->highThreadSpinbox, &QSpinBox::valueChanged,
            this, &CannyExample::process_image_session);
}

CannyExample::~CannyExample() {
	delete ui;
}

void CannyExample::process_image_session() {

    int low = ui->lowThredSpinbox->value();
    int high = ui->highThreadSpinbox->value();

    if (low >= high) {
        high = low + 1;
        blockSignals(true);
        ui->highThreadSpinbox->setValue(high);
        blockSignals(false);
    }
    QImage image = ui->image_controller->image();
    if (image.isNull()) {
        return;
    }
    CVImage cvImage = QtAdaptTools::fromRGBQImage(image);
    CannyProcessor processor;
    processor.threholds_pair = { low, high };
    processor.process(cvImage);
    QImage new_image = QtAdaptTools::toDisplayableImage(cvImage);
    ui->image_displayer->setProcessedImage(new_image);
}
