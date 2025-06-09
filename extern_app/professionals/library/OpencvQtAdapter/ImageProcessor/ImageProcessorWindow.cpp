#include "ImageProcessorWindow.h"
#include "./ui_ImageProcessorWindow.h"
#include "ImageProcessor/image_processing_example/blur_image/BlurExample.h"
#include "image_processing_example/gray_image/GrayExample.h"
#include <QLabel>
ImageProcessorWindow::ImageProcessorWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::ImageProcessorWindow) {
	ui->setupUi(this);
    setup_panel();
}

ImageProcessorWindow::~ImageProcessorWindow() {
	delete ui;
}

void ImageProcessorWindow::setup_panel() {
    ToolsStackedWidget::PagePackage pack[] = {
        { .name = "Gray Image",
          .icon = QIcon(),
          .widget = new GrayExample(this) },
        { .name = "Blur Image",
          .icon = QIcon(),
          .widget = new BlurExample(this) }
    };

    for (const auto& each : pack) {
        ui->centralwidget->add_switchable_page(each);
    }
}
