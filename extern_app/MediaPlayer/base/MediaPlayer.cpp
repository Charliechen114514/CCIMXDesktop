#include "MediaPlayer.h"
#include "VideoPlayer.h"
#include "base/QtAdaptTools.h"
#include <QAudioOutput>
#include <QMediaMetaData>
#include <QMediaPlayer>
#include <qdebug.h>

namespace {
std::pair<QString, bool> adjust_media_status(const VideoPlayerOpenErrorCode code) {
	switch (code) {
	case VideoPlayerOpenErrorCode::NoError:
		/* video makes nosense */
		return { "", true };
		break;
	case VideoPlayerOpenErrorCode::DupOpen:
		return { "duplicate open", true };
		break;
	case VideoPlayerOpenErrorCode::FileUnExsited:
		return { "File is not exsited", false };
		break;
	case VideoPlayerOpenErrorCode::OpenFailed:
		return { "Unsupport to display video", false };
		break;
	}
	return { "Unknown error", false };
}
}

MediaPlayer::MediaPlayer(QObject* parent)
	: QObject { parent } {
	/* memory allocations */
	init_allocations();
	init_connections();
}

/* source shell be opened */
void MediaPlayer::setSource(const char* local_file) {
	if (isPlaying()) {
		close();
	}

	/* these shell try to open videos, if failed,
	 * thus, we shell think the video is not supported */
	videoPlayer->open(local_file);
	audioPlayer->setSource(QUrl::fromLocalFile(local_file));

	/* adapt to request the first frame */
	CVImage first_page;
	videoPlayer->peekFrame(first_page, 0);
	media_status.video_ready = first_page.image_valid();
	emit videoAvailable(first_page.image_valid(),
						QtAdaptTools::toQImage(first_page));
}

QString MediaPlayer::source() const {
	return videoPlayer->current_handle();
}

void MediaPlayer::setVolume(const float percentage) {
	audioPlayer->audioOutput()->setVolume(percentage);
}

float MediaPlayer::volume() const {
	return audioPlayer->audioOutput()->volume();
}

bool MediaPlayer::resume() {
	if (media_status.audio_ready) {
		audioPlayer->play();
	}

	if (media_status.video_ready) {
		videoPlayer->play();
	}

	return isPlaying();
}

bool MediaPlayer::pause() {
	audioPlayer->pause();
	videoPlayer->pause();
	return true;
}

bool MediaPlayer::close() {
	audioPlayer->stop();
	videoPlayer->close();
	return true;
}

bool MediaPlayer::isPlaying() const {
	return videoPlayer->is_playing() || audioPlayer->isPlaying();
}

void MediaPlayer::set_position(const qint64 position) {
	audioPlayer->setPosition(position);
	videoPlayer->setCurrentFrameMSec(position);
}

void MediaPlayer::init_allocations() {
	videoPlayer = new VideoPlayer(this);
	audioPlayer = new QMediaPlayer(this);
	QAudioOutput* audio = new QAudioOutput(this);
	audioPlayer->setAudioOutput(audio);
	audioPlayer->setVideoOutput(nullptr);
}

void MediaPlayer::init_connections() {
	/* process the sync issue */
	connect(videoPlayer, &VideoPlayer::frameReady,
			this, &MediaPlayer::process_sync);

	connect(videoPlayer, &VideoPlayer::openError, this,
			[this](const VideoPlayerOpenErrorCode code) {
				auto result = adjust_media_status(code);
				this->media_status.video_ready = result.second;
				this->media_status.video_discriptions = result.first;
			});

	connect(videoPlayer, &VideoPlayer::videoEnd,
			this, [this]() {
				emit mediaEnd();
			});

	connect(audioPlayer, &QMediaPlayer::mediaStatusChanged, this, [this](QMediaPlayer::MediaStatus status) {
		switch (status) {
		case QMediaPlayer::MediaStatus::InvalidMedia:
			qDebug() << "Invalid media";
			this->media_status.audio_ready = false;
			break;
		case QMediaPlayer::MediaStatus::EndOfMedia:
			qDebug() << "End of media";
			emit mediaEnd();
			break;
		case QMediaPlayer::MediaStatus::BufferedMedia:
		case QMediaPlayer::MediaStatus::LoadedMedia:
			extract_metainfo(); /* means the fallback */
		default:
			qDebug() << "Media status changed: " << status;
			this->media_status.audio_ready = true;
			break;
		}
		emit sourceOpened(media_status.audio_discriptions, media_status);
	});

	connect(audioPlayer, &QMediaPlayer::errorOccurred, this,
			[this](QMediaPlayer::Error error, const QString& errorString) {
				switch (error) {
				case QMediaPlayer::NoError:
					qDebug() << "No error";
					this->media_status.audio_ready = true;
					break;
				default:
					qDebug() << "Error occurred: " << error;
					this->media_status.audio_ready = false;
					this->media_status.audio_discriptions = errorString;
					break;
				}
				emit sourceOpened(errorString, media_status);
			});

	connect(audioPlayer, &QMediaPlayer::durationChanged,
			this, &MediaPlayer::handle_sync_duration);

	connect(audioPlayer, &QMediaPlayer::positionChanged,
			this, &MediaPlayer::handle_sync_position);
}

void MediaPlayer::process_sync(const CVImage& current_frame) {
	// fetch the time for current frame
	qint64 audio_time = audioPlayer->position();
	qint64 video_time = videoPlayer->currentFrameMSec();
	while (video_time + mis_sync_seconds < audio_time) {
		videoPlayer->escapeFrame(); // escape one frame
		video_time = videoPlayer->currentFrameMSec();
	}

	/* now, we ensure the frame is ready to display */
	emit display_frame(QtAdaptTools::toQImage(current_frame));
}

void MediaPlayer::handle_sync_duration(qint64 durations) {
	/* Audio is unavailable */
	if (durations == 0) {
		durations = videoPlayer->total_msecs();
	}
	/* update status */
	this->durations = durations;
	emit durationChanged(durations);
}

void MediaPlayer::handle_sync_position(qint64 position) {
	/* Audio is unavailable */
	if (position == 0) {
		position = videoPlayer->currentFrameMSec();
	}
	/* update status */
	this->position = position;
	emit positionChanged(position);
}

void MediaPlayer::extract_metainfo() {
	qDebug() << "extracting media info";
	MediaInfo info;
	const QMediaMetaData meta = audioPlayer->metaData();
	info.title = meta.stringValue(QMediaMetaData::Title);
	info.author = meta.stringValue(QMediaMetaData::Author);
	info.albumTitle = meta.stringValue(QMediaMetaData::AlbumTitle);
	info.albumArtist = meta.stringValue(QMediaMetaData::AlbumArtist);
	info.composer = meta.stringValue(QMediaMetaData::Composer);
	info.genre = meta.stringValue(QMediaMetaData::Genre);
	info.durationMs = meta.value(QMediaMetaData::Duration).toLongLong();
	info.date = meta.stringValue(QMediaMetaData::Date);
	info.trackNumber = meta.value(QMediaMetaData::TrackNumber).toInt();
	info.audioBitRate = meta.value(QMediaMetaData::AudioBitRate).toInt();
	info.audioCodec = meta.stringValue(QMediaMetaData::AudioCodec);
	info.mediaType = meta.stringValue(QMediaMetaData::MediaType);
	info.publisher = meta.stringValue(QMediaMetaData::Publisher);

	emit metaDataAvailable(info);
}
