#include "ImageWalkerWindow.h"

#include "ui_ImageWalkerWindow.h"
#include <QFileDialog>
#include <QMessageBox>

void ImageWalkerWindow::handle_error(const ImageBrowser::ErrorType e) {
	switch (e) {
	case ImageBrowser::ErrorType::IMAGEREQ_OVERFLOW: {
		auto result = QMessageBox::question(this, "Error occurs", "You have reached the last one, go back?");
		if (result == QMessageBox::Yes) {
			ui->image_display_widget->show_start();
		}
	} break;
	case ImageBrowser::ErrorType::IMAGEREQ_UNDERFLOW: {
		auto result = QMessageBox::question(this, "Error occurs", "You have reached the first one, go last one?");
		if (result == QMessageBox::Yes) {
			ui->image_display_widget->show_end();
		}
	} break;
	case ImageBrowser::ErrorType::IMAGEREQ_LOST: {
		auto result = QMessageBox::question(this, "Error occurs", "You have reached the unexsited one, go first one?");
		if (result == QMessageBox::Yes) {
			ui->image_display_widget->show_start();
		}
	} break;

	case ImageBrowser::ErrorType::IMAGEREQ_EMPTY:
		auto result = QMessageBox::question(this, "Error occurs", "You have no images here, go first one?");
		if (result == QMessageBox::Yes) {
			ui->image_display_widget->show_start();
		}
		break;
	}
}

ImageWalkerWindow::ImageWalkerWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::ImageWalkerWindow) {
	ui->setupUi(this);

	init_connections();
}

ImageWalkerWindow::~ImageWalkerWindow() {
	delete ui;
}

void ImageWalkerWindow::init_connections() {
	connect(ui->actionexit, &QAction::triggered,
			this, &ImageWalkerWindow::close);
	connect(ui->actionset_dirent, &QAction::triggered,
			this, [this]() {
				QString dir = QFileDialog::getExistingDirectory(this, "Select a dirent", ".");
				if (dir.isEmpty())
					return;
				ui->image_display_widget->enDirSupports(dir);
			});
	connect(ui->actionfileview, &QAction::triggered,
			ui->image_display_widget, &ImageBrowser::oppose_fileview_visible);
	connect(ui->actionnext, &QAction::triggered,
			ui->image_display_widget, &ImageBrowser::show_next);
	connect(ui->actionend, &QAction::triggered,
			ui->image_display_widget, &ImageBrowser::show_end);
	connect(ui->actionprev, &QAction::triggered,
			ui->image_display_widget, &ImageBrowser::show_prev);
	connect(ui->actionstart, &QAction::triggered,
			ui->image_display_widget, &ImageBrowser::show_start);
	connect(ui->image_display_widget, &ImageBrowser::errorOccur,
			this, &ImageWalkerWindow::handle_error);
	connect(ui->actionclear, &QAction::triggered,
			ui->image_display_widget, &ImageBrowser::clear);
	connect(ui->actiondelete, &QAction::triggered,
			ui->image_display_widget, &ImageBrowser::remove_select);
	connect(ui->actioninfo, &QAction::triggered,
			ui->image_display_widget, &ImageBrowser::show_infoWindow);
}
