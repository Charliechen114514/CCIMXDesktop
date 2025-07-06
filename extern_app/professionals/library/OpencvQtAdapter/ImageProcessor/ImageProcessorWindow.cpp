#include "ImageProcessorWindow.h"
#include "./ui_ImageProcessorWindow.h"
#include "ImageProcessor/image_processing_example/contours_query/ContoursQueryExample.h"
#include "ImageProcessor/image_processing_example/face_detection/FaceDetectionExample.h"
#include "ImageProcessor/image_processing_example/hist_drawer/HistDrawer.h"
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
        { "Gray Image",
          QIcon(":/icons/greyscale.png"),
          new GrayExample(this) },
        { "Blur Image",
          QIcon(":/icons/blur.png"),
          new BlurExample(this) },
        { "Canny Image",
          QIcon(":/icons/canny.png"),
          new CannyExample(this) },
        { "Find Contours",
          QIcon(":/icons/contours.png"),
          new ContoursQueryExample(this) },
        { "Hist Creator",
          QIcon(":/icons/histquery.png"),
          new HistDrawer(this) },
        { "Face Detector",
          QIcon(":/icons/face_detection.png"),
          new FaceDetectionExample(this) }
    };

    for (const auto& each : pack) {
        ui->centralwidget->add_switchable_page(each);
    }
}
