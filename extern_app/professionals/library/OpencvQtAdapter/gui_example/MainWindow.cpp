#include "MainWindow.h"
#include "./ui_MainWindow.h"
#include "core_library/cvimage/CVImagePrivateOpencvImp.h"
#include "core_library/videoplayer_src/VideoPlayer.h"
#include <QFileDialog>
QImage raw_image_to_qimage(const CVImage& image) {
	cv::Mat raw_image = dynamic_cast<CVImageOpencvImpl*>(image.impl_ptr())->raw_image;
	/* convert the raw image to QImage */
	return QImage(
		raw_image.data,
		raw_image.cols,
		raw_image.rows,
		static_cast<int>(raw_image.step[0]),
		QImage::Format_RGB888);
}

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
	ui->setupUi(this);
	video_player = new VideoPlayer(this);
}

MainWindow::~MainWindow() {
	delete ui;
}

void MainWindow::on_btn_open_clicked() {

	QString file_path = QFileDialog::getOpenFileName(this, "Select Video File", ".", "*.mp4");
	if (file_path.isEmpty()) {
		return;
	}
	video_player->open(file_path.toStdString().c_str());
}

void MainWindow::on_btn_play_clicked() {
	if (video_player->is_playing()) {
		return;
	} else {
		video_player->play();
	}
	connect(video_player, &VideoPlayer::frameReady, this, [this](const CVImage image) {
		ui->label->setPixmap(QPixmap::fromImage(raw_image_to_qimage(image)));
	});
	connect(video_player, &VideoPlayer::openError, this, [](const VideoPlayerOpenErrorCode error) {
		switch (error) {
		case VideoPlayerOpenErrorCode::DupOpen:
			qDebug() << "Video is already opened!";
			break;
		case VideoPlayerOpenErrorCode::FileUnExsited:
			qDebug() << "File does not exist!";
			break;
		default:
			break;
		}
	});
}

void MainWindow::on_btn_stop_clicked() {
	video_player->pause();
}
