#include "ContoursQueryExample.h"
#include "CVImage.h"
#include "ContoursQueryProc.h"
#include "QtAdaptTools.h"
#include "ui_ContoursQueryExample.h"
#include <QMessageBox>
ContoursQueryExample::ContoursQueryExample(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::ContoursQueryExample) {
	ui->setupUi(this);
    connect(ui->image_controller, &ImageProcessingWidget::image_loaded,
            ui->image_displayer, &ImageResultDisplayer::setRawImage);
    connect(ui->image_controller, &ImageProcessingWidget::request_processing,
            this, &ContoursQueryExample::process_image_session);
    ui->image_controller->process_direct_load(":/example_image/lena.jpg");
    // setup the panels
    QStringList selections;
    auto result = Processor::ContoursQuery::keys();
    for (const auto& i : result) {
        selections << QString::fromStdString(i);
    }
    ui->method_selections->addItems(selections);
    connect(ui->method_selections, &QComboBox::textActivated,
            this, &ContoursQueryExample::process_image_session);
}

void ContoursQueryExample::process_image_session() {
    Processor::ContoursQuery::Method method {};
    try {
        method = Processor::ContoursQuery::fromString(ui->method_selections->currentText().toStdString());
    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Invalid Argument!", "Ah shit, invalid argument!");
        return;
    }
    QImage image = ui->image_controller->image();
    if (image.isNull()) {
        return;
    }
    CVImage cvImage = QtAdaptTools::fromRGBQImage(image);
    ContoursQueryProc proc;
    proc.method = method;
    proc.process(cvImage);
    QImage new_image = QtAdaptTools::toDisplayableImage(cvImage);
    ui->image_displayer->setProcessedImage(new_image);
}

ContoursQueryExample::~ContoursQueryExample() {
	delete ui;
}
