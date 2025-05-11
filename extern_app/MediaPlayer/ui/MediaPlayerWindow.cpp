#include "MediaPlayerWindow.h"
#include "base/MediaPlayer.h"
#include "core/MediaEnableSelectFactory.h"
#include "core/UiTools.h"
#include "ui/MediaInfoWindow.h"
#include "ui_MediaPlayerWindow.h"
#include <QFileDialog>
class MediaPlayerWindowHelper {
public:
	static void handle_displayError(
		MediaPlayerWindow* window,
		const QString& sources,
		MediaPlayer::MediaPlayerStatus status) {
		/* process the error */
	}
};

MediaPlayerWindow::MediaPlayerWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MediaPlayerWindow) {
	ui->setupUi(this);
	init_memories();
	init_connections();
	post_init_ui();
}

void MediaPlayerWindow::open_media() {
	QString file = MediaEnableSelectFactory::get_enabled_select_medias_fromdialog(
		this, "Select Media File");
	if (file.isEmpty())
		return;
	mediaPlayer->setSource(file.toStdString().c_str());
}

void MediaPlayerWindow::toggle_playing_status() {
	is_playing = !is_playing;
	process_playing_status();
	ui->music_widget->setStatus(is_playing);
	is_playing ? mediaPlayer->resume() : mediaPlayer->pause();
}

MediaPlayerWindow::~MediaPlayerWindow() {
	delete ui;
}

void MediaPlayerWindow::handle_display_src(bool available, const QImage& image) {
	video_available = available;
	if (available) {
		/* display the image */
		ui->music_widget->hide();
		ui->frame_label->show();
		ui->frame_label->setPixmap(QPixmap::fromImage(image));
	} else {
		/* handle the error */
		post_do_video_unavailable();
	}
	ui->sound_slider->setValue(mediaPlayer->volume() * 100);
	ui->position_slidebar->setEnabled(true);
	ui->btn_status_change->setEnabled(true);
}

void MediaPlayerWindow::post_do_video_unavailable() {
	ui->music_widget->show();
	ui->frame_label->hide();
}

void MediaPlayerWindow::post_init_ui() {
	ui->music_widget->show();
	ui->frame_label->hide();

	ui->position_slidebar->setEnabled(false);
	ui->btn_status_change->setEnabled(false);
	ui->btn_status_change->setIconSize(QSize(50, 50));
	ui->btn_status_change->setIcon(QIcon(":/icons/media_paused.png"));
}

void MediaPlayerWindow::process_playing_status() {
	if (is_playing) {
		/* managing the playing one */
		ui->btn_status_change->setIcon(QIcon(":/icons/media_displaying.png"));
	} else {
		ui->btn_status_change->setIcon(QIcon(":/icons/media_paused.png"));
	}
}

void MediaPlayerWindow::handle_imageDisplay(const QImage& image) {
	ui->frame_label->setPixmap(QPixmap::fromImage(image));
}

void MediaPlayerWindow::handle_new_durations(qint64 duration) {
	static constexpr const unsigned short START_TIME_FOR_LABEL = 0;
	ui->current_time_label->setText(UiTools::toMediaTypicalTimeStr(START_TIME_FOR_LABEL));
	ui->total_time_label->setText(UiTools::toMediaTypicalTimeStr(duration));

	auto time_cast = UiTools::downcast_to_sliderable_period(START_TIME_FOR_LABEL, duration);
	ui->position_slidebar->setMinimum(time_cast.first);
	ui->position_slidebar->setMaximum(time_cast.second);
}

void MediaPlayerWindow::handle_position_changed(qint64 position) {
	ui->current_time_label->setText(UiTools::toMediaTypicalTimeStr(position));
	auto time_cast = UiTools::downcast_to_sliderable_position(position);
	ui->position_slidebar->setValue(time_cast);
}

void MediaPlayerWindow::handle_media_end() {
	qDebug() << "media reached its end";
	ui->btn_status_change->setIcon(QIcon(":/icons/media_paused.png"));
}

void MediaPlayerWindow::handle_slider_position_changed(int position) {
	if (!manual_sliding)
		return; /* Normal plays don't make sense of change */
	/* thus the user is sliding */
	ui->current_time_label->setText(UiTools::toMediaTypicalTimeStr(position));
}

void MediaPlayerWindow::handle_slider_pressed() {
	manual_sliding = true;
	/* when pressed, we should pause the media */
	mediaPlayer->pause();
	ui->music_widget->setStatus(false);
	is_playing = false;
	process_playing_status();
}

void MediaPlayerWindow::handle_slider_released() {
	/* continue for the resume */
	manual_sliding = false;
	qDebug() << "set the time to" << UiTools::toMediaTypicalTimeStr(UiTools::upcast_to_mseconds(ui->position_slidebar->value()));
	mediaPlayer->set_position(UiTools::upcast_to_mseconds(ui->position_slidebar->value()));
	/* resume the media */
	mediaPlayer->resume();
	is_playing = true;
	ui->music_widget->setStatus(true);
	process_playing_status();
}

void MediaPlayerWindow::init_memories() {
	mediaPlayer = new MediaPlayer(this);
	infoWindow = new MediaInfoWindow(this);
}

void MediaPlayerWindow::init_core_connections() {
	/* if the video owns the frame, play the first */
	connect(mediaPlayer, &MediaPlayer::videoAvailable,
			this, &MediaPlayerWindow::handle_display_src);
	/* when the sources get the errors, thus it working */
	connect(mediaPlayer, &MediaPlayer::sourceOpened,
			this, [this](const QString source, MediaPlayer::MediaPlayerStatus status) {
				/* process the error */
				MediaPlayerWindowHelper::handle_displayError(this, source, status);
			});

	connect(ui->btn_status_change, &QPushButton::clicked,
			this, &MediaPlayerWindow::toggle_playing_status);

	connect(mediaPlayer, &MediaPlayer::display_frame,
			this, &MediaPlayerWindow::handle_imageDisplay);

	connect(mediaPlayer, &MediaPlayer::mediaEnd,
			this, &MediaPlayerWindow::handle_media_end);

	connect(mediaPlayer, &MediaPlayer::durationChanged,
			this, &MediaPlayerWindow::handle_new_durations);
	connect(mediaPlayer, &MediaPlayer::positionChanged,
			this, &MediaPlayerWindow::handle_position_changed);

	connect(mediaPlayer, &MediaPlayer::metaDataAvailable,
			infoWindow, &MediaInfoWindow::filled_metainfo);
}

void MediaPlayerWindow::init_ui_connections() {

	/* Tool Bars Connections */
	connect(ui->actionaction_open_media, &QAction::triggered,
			this, &MediaPlayerWindow::open_media);

	connect(ui->actionmedia_info, &QAction::triggered,
			infoWindow, &MediaInfoWindow::show);

	connect(ui->sound_slider, &QSlider::valueChanged,
			this, [this](int value) {
				mediaPlayer->setVolume(value / 100.0);
			});

	connect(ui->position_slidebar, &QSlider::valueChanged,
			this, &MediaPlayerWindow::handle_slider_position_changed);
	connect(ui->position_slidebar, &QSlider::sliderPressed,
			this, &MediaPlayerWindow::handle_slider_pressed);
	connect(ui->position_slidebar, &QSlider::sliderReleased,
			this, &MediaPlayerWindow::handle_slider_released);
}

void MediaPlayerWindow::init_connections() {
	init_core_connections();
	init_ui_connections();
}
