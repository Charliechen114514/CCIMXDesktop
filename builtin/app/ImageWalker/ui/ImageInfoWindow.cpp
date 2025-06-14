#include "ImageInfoWindow.h"
#include "ui_ImageInfoWindow.h"
#include <QFileInfo>
#include <QImageReader>
ImageInfoWindow::ImageInfoWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::ImageInfoWindow) {
	ui->setupUi(this);
    connect(ui->btn_quit, &QPushButton::clicked, this, &ImageInfoWindow::hide);
}

void ImageInfoWindow::set_image_path(const QString& path) {
	image_path = path;
	QFileInfo info(image_path);
	QImageReader reader(image_path);
	QImage image = reader.read();

	if (!image.isNull()) {
		ui->labelThumbnail->setImage(image);

		ui->labelFileName->setText(info.fileName());
		ui->labelFileSize->setText(QString("%1 MB").arg(info.size() / 1024.0 / 1024.0, 0, 'f', 2));
		ui->labelFilePath->setText(info.absoluteFilePath());

		ui->labelImageSize->setText(QString("%1 x %2").arg(image.width()).arg(image.height()));
		ui->labelDpi->setText(QString("%1 dpi").arg(image.dotsPerMeterX() * 0.0254, 0, 'f', 0));
		ui->labelDepth->setText(QString("%1 bits").arg(image.depth()));

		ui->labelCreated->setText(info.birthTime().toString("yyyy Year MM Month dd Day hh:mm:ss"));
		ui->labelModified->setText(info.lastModified().toString("yyyy Year MM Month dd Day hh:mm:ss"));
	}
}

ImageInfoWindow::~ImageInfoWindow() {
	delete ui;
}
