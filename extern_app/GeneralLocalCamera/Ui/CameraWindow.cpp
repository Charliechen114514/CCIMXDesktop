#include "CameraWindow.h"
#include "Core/CameraCapture.h"
#include "Core/CameraDeviceSelector.h"
#include "Core/PhotoSaver.h"
#include "Ui/DesktopToast.h"
#include "ui_CameraWindow.h"
#include <QFileDialog>
#include <QStandardPaths>
CameraWindow::CameraWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::CameraWindow) {
    ui->setupUi(this);
    toast = new DesktopToast(this);
    redirect(QStandardPaths::writableLocation(QStandardPaths::PicturesLocation));
    setup_internal();
}

void CameraWindow::fresh_cameralists() {
	ui->comboBox->clear();
	ui->comboBox->addItems(CameraDeviceSelector::scan_available_camerasnames());
	if (ui->comboBox->count() == 0) {
		/* thus no camera are found */
		ui->btn_oppose_camera->setEnabled(false);
		ui->btn_capture_once->setEnabled(false);
	} else {
		bool isOk = false;
		int num = ui->comboBox->itemText(0).toInt(&isOk);
		if (!isOk) {
			/* invalid transform */
			qDebug() << "invalid transform";
			toast->set_message("Can not init the selecting camera!");
			return;
		} else {
			ui->btn_oppose_camera->setEnabled(true);
			select(num);
			toast->set_message("switch the camera successfully!");
		}
	}
}

void CameraWindow::redirect(const QString path) {
	if (path.isEmpty())
		return;

	if (!PhotoSaver::dirSavable(path)) {
		toast->set_message("Can not save!");
		return;
	}

	cached_path = path;
	ui->lineEdit->setText(cached_path);
}

void CameraWindow::setup_internal() {
	fresh_cameralists();
	connect(ui->btn_exit, &QPushButton::clicked,
			this, &QApplication::exit);
	connect(ui->btn_refresh, &QPushButton::clicked,
			this, &CameraWindow::fresh_cameralists);
	connect(ui->btn_redirect, &QPushButton::clicked,
			this, [this]() {
				redirect(QFileDialog::getExistingDirectory(this, "selecting dirent", "."));
			});
	connect(ui->btn_capture_once, &QPushButton::clicked,
			this, &CameraWindow::capture_photo_once);
	connect(ui->actionexit, &QAction::triggered, this, &QApplication::exit);
	connect(ui->actionphoto, &QAction::triggered, this, &CameraWindow::capture_photo_once);
	connect(ui->actionfresh, &QAction::triggered, this, &CameraWindow::fresh_cameralists);
	ui->actionphoto->setEnabled(false);
}

void CameraWindow::select(int index) {
	camera_capture = new CameraCapture(index, this);
	camera_capture->bind_display_widget(ui->camera_display_widget);
}

void CameraWindow::process_oppose_state(bool prev_opened) {
	ui->btn_oppose_camera->setText(prev_opened ? "Open" : "Close");
	ui->btn_capture_once->setEnabled(!prev_opened);
	ui->actionphoto->setEnabled(!prev_opened);
	ui->actionfresh->setEnabled(prev_opened);
	ui->btn_refresh->setEnabled(prev_opened);
	ui->comboBox->setEnabled(prev_opened);
	prev_opened ? camera_capture->close() : camera_capture->start();
}

void CameraWindow::capture_photo_once() {
	if (!camera_capture->isActivate()) {
		return;
	}
	switch (
		PhotoSaver::saveOnce(
			ui->camera_display_widget->current_captures(),
			cached_path)) {

	case PhotoSaver::Error::SaveSuccess:
		toast->set_message("image is saved!");
		break;
	case PhotoSaver::Error::NullImage:
		toast->set_message("image is empty, so nothing saves!");
		break;
	case PhotoSaver::Error::DirUnsavable:
		toast->set_message("image is unsaved due to the none exsited dirent!");
		break;
	case PhotoSaver::Error::ImageSelfSaveFailed:
		toast->set_message("image is unsaved due to the image saving process failed!");
		break;
	}
}

CameraWindow::~CameraWindow() {
	delete camera_capture;
	delete ui;
}

void CameraWindow::on_btn_oppose_camera_clicked() {
	process_oppose_state(camera_capture->isActivate());
}
