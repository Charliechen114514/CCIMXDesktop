#include "MainWindow.h"
#include "DesktopToast.h"
#include "ui_MainWindow.h"
#include <QCameraDevice>
#include <QDateTime>
#include <QFile>
#include <QFileDialog>
#include <QImageCapture>
#include <QMediaDevices>
#include <QMessageBox>
#include <QStandardPaths>
#include <QVideoWidget>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
	ui->setupUi(this);
	setup_window();
	fresh_available_camera_once();
	connect_connections();
}

void MainWindow::fresh_available_camera_once() {
	ui->camera_list_selector->clear();
	const QList<QCameraDevice> cameras = QMediaDevices::videoInputs();
	QStringList items;
	for (const auto& each_cameras : cameras) {
		items << each_cameras.description();
	}
	ui->camera_list_selector->addItems(items);
	if (cameras.empty()) {
		/* Thus, no available camera */
		qDebug() << "No available cameras";
		ui->btn_oppose_camera->setEnabled(false);
		return;
	} else {
		process_post_refresh(cameras);
	}
}

MainWindow::~MainWindow() {
	delete ui;
}

void MainWindow::setup_window() {

	/* available for the image capture then */
	image_capture = new QImageCapture(this);
	connect(image_capture, &QImageCapture::imageSaved, this, [this](int id, const QString& filePath) {
		toast->set_message("Saved to: " + filePath);
	});

	captureSession.setImageCapture(image_capture);
	/* display init */
	videoWidget = new QVideoWidget(ui->camera_base_widget);
	ui->camera_base_widget->layout()->addWidget(videoWidget);
	ui->btn_capture_once->setEnabled(false);
	/* setup the desktop toast */
	toast = new DesktopToast(this);

	/* init saves */
	cached_path = QStandardPaths::writableLocation(QStandardPaths::PicturesLocation);
	ui->lineEdit->setText(cached_path);
}

void MainWindow::redirect_path() {
	QString new_path = QFileDialog::getExistingDirectory(this, "Select place to save", ".");
	if (new_path.isEmpty()) {
		return;
	}
	cached_path = new_path;
	ui->lineEdit->setText(cached_path);
}

void MainWindow::connect_connections() {
	connect(ui->actionexit, &QAction::triggered,
			this, &QApplication::exit);
	connect(ui->actionphoto, &QAction::triggered,
			this, &MainWindow::on_btn_capture_once_clicked);
	connect(ui->actionrefresh, &QAction::triggered,
			this, &MainWindow::fresh_available_camera_once);
	connect(ui->actionswitch_dirent, &QAction::triggered,
			this, &MainWindow::redirect_path);
}

/* working as the camera operations */
void MainWindow::on_btn_oppose_camera_clicked() {
    process_once_switch(camera->isActive());
}

void MainWindow::
	process_post_refresh(const QList<QCameraDevice>& cameras) {
	ui->btn_oppose_camera->setEnabled(true);
	/* setup the combo box */
	ui->camera_list_selector->setCurrentIndex(0);
	camera.reset(new QCamera(cameras.first()));
	captureSession.setCamera(camera.get());
	captureSession.setVideoOutput(videoWidget);
}

void MainWindow::process_once_switch(const bool current_state) {
	current_state ? camera->stop() : camera->start();
	ui->camera_list_selector->setEnabled(current_state);
	ui->btn_oppose_camera->setText(current_state ? "Open" : "Close");

	ui->btn_capture_once->setEnabled(!current_state);
	ui->actionphoto->setEnabled(!current_state);

	ui->btn_refresh->setEnabled(current_state);
	ui->actionrefresh->setEnabled(current_state);
}

/* exit the applications */
void MainWindow::on_btn_exit_clicked() {
	QApplication::exit();
}

/* button refresh */
void MainWindow::on_btn_refresh_clicked() {
	fresh_available_camera_once();
}

void MainWindow::on_camera_list_selector_textActivated(const QString& arg1) {
	const QList<QCameraDevice> cameras = QMediaDevices::videoInputs();
	for (const auto& each_cameras : cameras) {
		if (each_cameras.description() == arg1) {
			/* thus that's it */
			camera.reset(new QCamera(each_cameras));
			captureSession.setCamera(camera.get());
			captureSession.setVideoOutput(videoWidget);
			return;
		}
	}

	qDebug() << "Can not match the camera! " << arg1;
}

void MainWindow::on_btn_capture_once_clicked() {
	if (!camera) {
		qDebug() << "camera is not even exsited!";
		toast->set_message("Camera is not init, which is not expected!");
		return;
	}

	if (!camera->isActive()) {
		qDebug() << "camera is not even activate!";
		toast->set_message("Camera is not opened! you would never enjoy a black shoots right");
		return;
	}

	qDebug() << "check the save dir, save dirent is" << cached_path;
	if (!QFile::exists(cached_path)) {
		qDebug() << "but the dirent is not exsit";
		return;
	}

	QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd_HH-mm-ss");
	QString filePath = cached_path + "/" + timestamp + ".jpg";

	if (QMessageBox::question(this, "Saved?", "Save Pictures to the path: " + filePath + "?") == QMessageBox::StandardButton::Yes) {
		image_capture->captureToFile(filePath);
	}
}

void MainWindow::on_btn_redirect_clicked() {
	redirect_path();
}
