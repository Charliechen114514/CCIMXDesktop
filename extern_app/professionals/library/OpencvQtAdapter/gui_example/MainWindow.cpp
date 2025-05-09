#include "MainWindow.h"
#include "./ui_MainWindow.h"
#include "core_library/cvimage/CVImagePrivateOpencvImp.h"
#include "core_library/videoplayer/VideoPlayer.h"
#include <QAudioOutput>
#include <QFileDialog>
#include <QMediaPlayer>

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
	audio_player = new QMediaPlayer(this);
	audio_output = new QAudioOutput(this);
    audio_output->setVolume(VOLUMN);
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
	audio_player->setSource(QUrl::fromLocalFile(file_path.toStdString().c_str()));
	audio_player->setVideoOutput(nullptr);
	audio_player->setAudioOutput(audio_output);
}

void MainWindow::on_btn_play_clicked() {
	if (video_player->is_playing()) {
		return;
	} else {
		video_player->play();
		audio_player->play();
	}
	connect(video_player, &VideoPlayer::frameReady, this, [this](const CVImage image) {
		qint64 audio_time = audio_player->position(); // 当前音频播放时间（你需要确认该接口是否存在）
		qint64 video_time = video_player->currentFrameMSec(); // 当前视频帧的时间戳（你也要实现或确认）

		while (video_time + MainWindow::MAX_MISTCH < audio_time) {
			video_player->escapeFrame(); // 跳过一帧
			video_time = video_player->currentFrameMSec(); // 获取跳帧后的新时间戳
		}

		// 此时视频已经追上或接近音频，显示当前帧
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
	audio_player->pause();
}
