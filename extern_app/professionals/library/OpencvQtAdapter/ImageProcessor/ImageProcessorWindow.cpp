#include "ImageProcessorWindow.h"
#include "./ui_ImageProcessorWindow.h"
#include "ImageProcessor/image_processing_example/contours_query/ContoursQueryExample.h"
#include "image_processing_example/blur_image/BlurExample.h"
#include "image_processing_example/canny_example/CannyExample.h"
#include "image_processing_example/gray_image/GrayExample.h"
#include <QLabel>
ImageProcessorWindow::ImageProcessorWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::ImageProcessorWindow) {
	ui->setupUi(this);
    connect(ui->actionquit, &QAction::triggered, this, &ImageProcessorWindow::close);
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
          .widget = new BlurExample(this) },
        { .name = "Canny Image",
          .icon = QIcon(),
          .widget = new CannyExample(this) },
        { .name = "Find Contours",
          .icon = QIcon(),
          .widget = new ContoursQueryExample(this) }
    };

    for (const auto& each : pack) {
        ui->centralwidget->add_switchable_page(each);
    }
}
