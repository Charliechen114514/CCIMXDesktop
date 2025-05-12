#include "MediaPlayerWindow.h"
#include "PlayListMainWindow.h"
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
	medialist->enqueue_play({ file });
	/* set the media */
	MediaListMails mails = medialist->fetch_first_play();
	handle_according_mails(mails);
}

void MediaPlayerWindow::open_medias() {
	QStringList files = MediaEnableSelectFactory::get_all_enabled_select_medias_fromdialog(
		this, "Select Media Files");
	if (files.isEmpty())
		return;
	medialist->enqueue_play(files);
	/* set the media */
	MediaListMails mails = medialist->fetch_first_play();
	handle_according_mails(mails);
}

void MediaPlayerWindow::toggle_playing_status() {
	is_playing = !is_playing;
	process_playing_status();
	ui->music_widget->setStatus(is_playing);
	is_playing ? mediaPlayer->resume() : mediaPlayer->pause();
}

void MediaPlayerWindow::forward10sec() {
	/* if there is less then 10 secs, reject */
	if (mediaPlayer->get_durations() - mediaPlayer->get_position() < UiTools::upcast_to_mseconds(10)) {
		/* no enough 10 secs, set to the last end */
		mediaPlayer->set_position(mediaPlayer->get_durations());
		return;
	}
	auto position = mediaPlayer->get_position() + UiTools::upcast_to_mseconds(10);
	mediaPlayer->set_position(position);
}

void MediaPlayerWindow::backward10sec() {

	if (mediaPlayer->get_position() < UiTools::upcast_to_mseconds(10)) {
		/* no enough 10 secs */
		mediaPlayer->set_position(0);
		return;
	}
	auto position = mediaPlayer->get_position() - UiTools::upcast_to_mseconds(10);
	mediaPlayer->set_position(position);
}

void MediaPlayerWindow::flow_mode_once() {
	medialist->flow_mode();
	process_playmode_switching();
	handle_according_mails(medialist->fetch_current_play());
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
	ui->btn_goforward->setEnabled(true);
	ui->btn_gobackward->setEnabled(true);
	ui->display_label_widget->setText(UiTools::toScrollLabelText(mediaPlayer->source()));
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
	ui->btn_goforward->setEnabled(false);
	ui->btn_gobackward->setEnabled(false);
	ui->btn_next_one->setEnabled(false);
	ui->btn_prev_one->setEnabled(false);
	ui->btn_status_change->setIconSize(QSize(50, 50));
	ui->btn_status_change->setIcon(QIcon(":/icons/media_paused.png"));
	process_playmode_switching();
}

void MediaPlayerWindow::process_playing_status() {
	ui->music_widget->setStatus(is_playing);
	if (is_playing) {
		/* managing the playing one */
		ui->btn_status_change->setIcon(QIcon(":/icons/media_displaying.png"));
	} else {
		ui->btn_status_change->setIcon(QIcon(":/icons/media_paused.png"));
	}
}

void MediaPlayerWindow::process_playmode_switching() {
	CCMediaPlayList::PlayMode mode = medialist->get_play_mode();
	switch (mode) {
	case CCMediaPlayList::PlayMode::OneShot:
		ui->btn_mode_flow->setIcon(QIcon(":/icons/single.png"));
		break;
	case CCMediaPlayList::PlayMode::OneCycle:
		ui->btn_mode_flow->setIcon(QIcon(":/icons/single_recycle.png"));
		break;
	case CCMediaPlayList::PlayMode::ListPlay:
		ui->btn_mode_flow->setIcon(QIcon(":/icons/listplay.png"));
		break;
	case CCMediaPlayList::PlayMode::ListCycle:
		ui->btn_mode_flow->setIcon(QIcon(":/icons/listrecycle.png"));
		break;
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
	process_playing_status();
}

void MediaPlayerWindow::handle_according_mails(const MediaListMails mails) {
	ui->btn_next_one->setEnabled(mails.next_enabled);
	ui->btn_prev_one->setEnabled(mails.prev_enabled);
	if (mails.current_playing.isEmpty()) {
		return; /* invalid */
	}
	if (mediaPlayer->isPlaying()) {
		mediaPlayer->pause();
		is_playing = false;
		process_playing_status();
	}
	mediaPlayer->setSource(mails.current_playing.toStdString().c_str());
	toggle_playing_status();
}

void MediaPlayerWindow::init_memories() {
	mediaPlayer = new MediaPlayer(this);
	infoWindow = new MediaInfoWindow(this);
	medialist = new CCMediaPlayList(this);
	playListWindow = new PlayListMainWindow(this);
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

	connect(ui->actionimport_medias, &QAction::triggered,
			this, &MediaPlayerWindow::open_medias);

	connect(ui->actionmedia_info, &QAction::triggered,
			infoWindow, &MediaInfoWindow::show);

	connect(ui->sound_slider, &QSlider::valueChanged,
			this, [this](int value) {
				mediaPlayer->setVolume(value / 100.0);
			});

	connect(ui->actionexit, &QAction::triggered,
			this, &MediaPlayerWindow::close);

	connect(ui->btn_goforward, &QPushButton::clicked,
			this, &MediaPlayerWindow::forward10sec);
	connect(ui->btn_gobackward, &QPushButton::clicked,
			this, &MediaPlayerWindow::backward10sec);

	connect(ui->btn_status_change, &QPushButton::clicked,
			this, &MediaPlayerWindow::toggle_playing_status);

	connect(ui->btn_next_one, &QPushButton::clicked,
			this, [this]() {
				handle_according_mails(medialist->fetch_next_play());
			});

	connect(ui->btn_prev_one, &QPushButton::clicked,
			this, [this]() {
				handle_according_mails(medialist->fetch_prev_play());
			});

	connect(ui->btn_mode_flow, &QPushButton::clicked,
			this, &MediaPlayerWindow::flow_mode_once);

	connect(ui->position_slidebar, &QSlider::valueChanged,
			this, &MediaPlayerWindow::handle_slider_position_changed);
	connect(ui->position_slidebar, &QSlider::sliderPressed,
			this, &MediaPlayerWindow::handle_slider_pressed);
	connect(ui->position_slidebar, &QSlider::sliderReleased,
			this, &MediaPlayerWindow::handle_slider_released);

	/* playlist info window */
	connect(ui->actionopen_medialist, &QAction::triggered,
			playListWindow, [this]() {
				playListWindow->from_media_list(medialist->actualList());
				playListWindow->show();
			});
	connect(playListWindow, &PlayListMainWindow::refresh_media_list,
			this, [this]() {
				/* flush the media list */
				medialist->flush_play_list();
				handle_according_mails(medialist->fetch_first_play());
			});
	connect(playListWindow, &PlayListMainWindow::play_media,
			this, [this](const QString& media_src) {
				/* set the media */
				handle_according_mails(medialist->fetch_from_name(media_src));
			});
	connect(playListWindow, &PlayListMainWindow::delete_media,
			this, [this](const QString& media_src) {
				/* delete the media */
				medialist->remove_play_list({ media_src });
			});
}

void MediaPlayerWindow::init_connections() {
	init_core_connections();
	init_ui_connections();
}
