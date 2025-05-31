#include "SaveWindow.h"
#include "ui_SaveWindow.h"
#include <QFileDialog>
SaveWindow::SaveWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::SaveWindow) {
	ui->setupUi(this);
}

void SaveWindow::processSave() {
	auto name = QFileDialog::getSaveFileName(this, "where to save the image?", ".", "*.png;;*.jpg");
	if (name.isEmpty()) {
		return;
	} else {
		holdingImage.save(name);
		close();
	}
}

void SaveWindow::processImageIssue() {
	ui->image_label->setPixmap(
		QPixmap::fromImage(
			holdingImage)
			.scaled(ui->image_label->size(), Qt::KeepAspectRatio));
	ui->height_spinbox->setValue(holdingImage.height());
	ui->width_spinbox->setValue(holdingImage.width());
}

SaveWindow::~SaveWindow() {
	delete ui;
}

void SaveWindow::on_height_spinbox_valueChanged(int arg1) {
	holdingImage = holdingImage.scaledToHeight(arg1);
}

void SaveWindow::on_width_spinbox_valueChanged(int arg1) {
	holdingImage = holdingImage.scaledToWidth(arg1);
}

void SaveWindow::on_btn_save_clicked() {
	processSave();
}

void SaveWindow::on_btn_quit_clicked() {
	this->close();
}
