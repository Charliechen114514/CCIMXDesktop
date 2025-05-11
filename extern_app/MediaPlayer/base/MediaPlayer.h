#ifndef MEDIAPLAYER_H
#define MEDIAPLAYER_H
#include <QImage>
#include <QObject>
class QMediaPlayer;
class VideoPlayer;
class QLabel;
class CVImage;
/*
 *  MediaPlayer is the wrapper of
 *  VideoPlayer and AudioPlayer, with the
 *  sync of video and audio basically
 */

enum class MediaError {
	NO_ERROR,
	UNEXSITED_SOURCE,
	/* VEDIO_ONLY and SOUND_ONLY means the partial displays */
	VEDIO_ONLY,
	SOUND_ONLY,
	UNSUPPORT_SOURCE,
};

namespace MediaPlayerPublicSettings {
/* for some cases, it is rather accpetable for the mismatch */
using MisSyncDelay_t = unsigned int;
/* max delay we can accept */
static constexpr MisSyncDelay_t DEF_ACCPET_DELAY = 500;
};

struct MediaInfo {
	QString title;
	QString author;
	QString albumTitle;
	QString albumArtist;
	QString composer;
	QString genre;
	qint64 durationMs;
	QString date;

	int trackNumber;
	int audioBitRate;
	QString audioCodec;
	QString mediaType;
	int sampleRate;
	QString publisher;
	QImage coverImage;
};

/*
 * Author here in 2025.5.10
 * In Current Version, Only OpenCV is supported for the video play
 * and the audio is only supported by QMediaPlayer, with current
 * ALSA is used for the audio play in IMX6ULL, so for cross compilers
 * you must cross compile with ALSA support
 */
class MediaPlayer : public QObject {
	Q_OBJECT
public:
	struct MediaPlayerStatus {
		/* media status */
		bool audio_ready { false };
		bool video_ready { false };
		/* What has been fucking happened */
		QString video_discriptions {};
		QString audio_discriptions {};
	};

	explicit MediaPlayer(QObject* parent = nullptr);
	Q_DISABLE_COPY(MediaPlayer);
	/* open media */
	void setSource(const char* local_file);
	/* the percentage of the volumn */
	void setVolume(const float percentage);
	/* volumn  */
	float volume() const;
	/* get the all mseconds of the media */
	inline qint64 get_durations() const { return durations; }
	/* get the current position */
	inline qint64 get_position() const { return position; }

	/*
	 * start the display if, the source is displayable
	 * and source is ready
	 */
	bool resume();
	/*
	 *	terminate for the request
	 */
	bool pause();
	/* close the source, this means a hard close */
	bool close();
	/* see if the audio is playing thus */
	/* for default, if one is playing, the mediaplayer is playing :) */
	bool isPlaying() const;

	/* Yet set the default mis sync tolerance */
	inline void set_accept_missync_msecond(
		const unsigned int msec
		= MediaPlayerPublicSettings::DEF_ACCPET_DELAY) {
		mis_sync_seconds = msec;
	}

	/* moves to the target positions */
	void set_position(const qint64 position);
signals:
	/* for those who expect to use callback */
	void display_frame(QImage image);
	/* volumn changed signals */
	void volumeChanged(float percentage);
	/* emit changed sources */
	void sourceOpened(const QString source, /* At which sources */
					  MediaPlayer::MediaPlayerStatus status); /* for what errors */
	/* frame is avaible */
	void videoAvailable(bool sourceAvailable, const QImage firstPage);
	/* media is end */
	void mediaEnd();
	/* duration sessions */
	void durationChanged(qint64 new_durantion);
	/* position accessied */
	void positionChanged(qint64 position);

	/* meta available */
	void metaDataAvailable(const MediaInfo info);

private:
	/* QMediaPlayer is expected to use Audio */
	QMediaPlayer* audioPlayer { nullptr };
	/* VideoPlayer is expected to display the video */
	VideoPlayer* videoPlayer { nullptr };
	/* for status holder */
	MediaPlayerStatus media_status;
	MediaPlayerPublicSettings::MisSyncDelay_t
		mis_sync_seconds { MediaPlayerPublicSettings::DEF_ACCPET_DELAY };
	qint64 durations {};
	qint64 position {};

	/* functions */

	/* invoke with initing */
	void init_allocations();
	void init_connections();
	/* for most cases in IMX6ULL Alpha board,
	 * without ffmpeg hard decorder of video flow(as no chips support)
	 * things got fucking stuff (written in 2025.5.10 :(  )
	 */
	void process_sync(const CVImage& current_frame);
	void handle_sync_duration(qint64 durations);
	void handle_sync_position(qint64 position);
	void extract_metainfo();
};

#endif // MEDIAPLAYER_H
