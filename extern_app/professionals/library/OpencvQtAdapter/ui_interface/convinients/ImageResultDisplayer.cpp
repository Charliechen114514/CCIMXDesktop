#include "ImageResultDisplayer.h"
#include "ui_ImageResultDisplayer.h"

ImageResultDisplayer::ImageResultDisplayer(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::ImageResultDisplayer) {
	ui->setupUi(this);
}

ImageResultDisplayer::~ImageResultDisplayer() {
	delete ui;
}

ImageLabel* ImageResultDisplayer::rawImageLabel() {
    return ui->raw_image_label;
}

ImageLabel* ImageResultDisplayer::processedImageLabel() {
    return ui->result_label_displayer;
}

void ImageResultDisplayer::setRawImage(const QImage& image) {
    ui->raw_image_label->setImage(image);
}

void ImageResultDisplayer::setProcessedImage(const QImage& image) {
    ui->result_label_displayer->setImage(image);
}
