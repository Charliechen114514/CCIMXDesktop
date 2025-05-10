#include "MainWindow.h"
#include "./ui_MainWindow.h"
#include "core_library/QtAdapter/QtAdaptTools.h"
#include "core_library/videoplayer/VideoPlayer.h"
#include <QAudioOutput>
#include <QFileDialog>
#include <QMediaPlayer>
MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
	ui->setupUi(this);
	video_player = new VideoPlayer(this);
	audio_player = new QMediaPlayer(this);
	audio_output = new QAudioOutput(this);
	audio_output->setVolume(VOLUMN);
	connect(video_player, &VideoPlayer::frameReady, this, &MainWindow::handle_frame);
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

void MainWindow::handle_frame(const CVImage& image) {
	// fetch the time for current frame
	qint64 audio_time = audio_player->position();
	qint64 video_time = video_player->currentFrameMSec();
	qDebug() << video_time << " " << audio_time;
	while (video_time + MainWindow::MAX_MISTCH < audio_time) {
		qDebug() << "escape frame: " << video_time << " " << audio_time;
		video_player->escapeFrame(); // escape one frame
		video_time = video_player->currentFrameMSec();
	}

	// the video and audio is nearly synced, thus display
	qDebug() << "display frame";
	ui->label->setPixmap(QPixmap::fromImage(QtAdaptTools::toQImage(image)));
}

void MainWindow::on_btn_play_clicked() {
	if (video_player->is_playing()) {
		return;
	}
	video_player->play();
	audio_player->play();
}

void MainWindow::on_btn_stop_clicked() {
	video_player->pause();
	audio_player->pause();
}
