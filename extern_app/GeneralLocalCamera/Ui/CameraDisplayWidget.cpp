#include "CameraDisplayWidget.h"
#include "ui_CameraDisplayWidget.h"

CameraDisplayWidget::CameraDisplayWidget(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::CameraDisplayWidget) {
	ui->setupUi(this);
}

void CameraDisplayWidget::setCurrentFrame(const QImage& image) {
	ui->display_label->setPixmap(
		QPixmap::fromImage(image).scaled(
			ui->display_label->size(),
			Qt::KeepAspectRatio,
			Qt::FastTransformation) /* fast transform, rt */
	);
}

QPixmap CameraDisplayWidget::current_captures() const {
	return ui->display_label->pixmap();
}

CameraDisplayWidget::~CameraDisplayWidget() {
	delete ui;
}
