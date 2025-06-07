#include "ImageProcessorWindow.h"
#include "./ui_ImageProcessorWindow.h"
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
        { .name = "cvt image",
          .icon = QIcon(),
          .widget = new QLabel("World", this) }
    };

    for (const auto& each : pack) {
        ui->centralwidget->add_switchable_page(each);
    }
}
