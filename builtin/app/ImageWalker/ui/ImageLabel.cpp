#include "ImageLabel.h"
#include <QPixmap>

ImageLabel::ImageLabel(QWidget* parent)
	: QLabel(parent) {
}

void ImageLabel::setImage(const QImage& image) {
	currentImage = image;
	if (!currentImage.isNull()) {
		setPixmap(QPixmap::fromImage(
			currentImage.scaled(size(), Qt::KeepAspectRatio, Qt::SmoothTransformation)));
	} else {
		clear();
	}
}

void ImageLabel::resizeEvent(QResizeEvent* event) {
	QLabel::resizeEvent(event);
	if (!currentImage.isNull()) {
		setPixmap(QPixmap::fromImage(
			currentImage.scaled(size(), Qt::KeepAspectRatio, Qt::SmoothTransformation)));
	}
}
