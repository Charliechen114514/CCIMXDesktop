#include "ImageProcessingWidget.h"
#include "CVImage.h"
#include "QtAdaptTools.h"
#include "ui_ImageProcessingWidget.h"
#include <QFileDialog>
#include <QLabel>
#include <QMessageBox>
namespace {
template <size_t N>
QString make_filters(const char* const (&filter)[N]) {
    QString result;
    for (size_t i = 0; i < N; ++i) {
        result += ("*." + QString::fromUtf8(filter[i]) + ";;");
    }
    return result;
}

}
ImageProcessingWidget::ImageProcessingWidget(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::ImageProcessingWidget) {
	ui->setupUi(this);
    connect(ui->btn_image_loaded, &QPushButton::clicked,
            this, &ImageProcessingWidget::process_raw_load);
}

ImageProcessingWidget::~ImageProcessingWidget() {
	delete ui;
}

void ImageProcessingWidget::displayed(QLabel* label) {
    label->setPixmap(
        QPixmap::fromImage(
            this->image_handling)
            .scaled(
                label->size(), Qt::KeepAspectRatio));
}

void ImageProcessingWidget::process_raw_load() {
    QString image_path = QFileDialog::getOpenFileName(
        this, "Select a loadable file",
        ".", make_filters(filters));
    if (image_path.isEmpty()) {
        return;
    }
    CVImage image;
    image.loadFile(image_path.toStdString().c_str());
    if (!image.image_valid()) {
        QMessageBox::critical(this, "Error", "Can not Load image from: " + image_path);
        return;
    }
    image_handling = QtAdaptTools::toDisplayableImage(image);
    emit image_loaded(image_handling);
}
