#ifndef MEDIAPLAYER_H
#define MEDIAPLAYER_H
#include <QImage>
#include <QObject>
class QMediaPlayer;
class VideoPlayer;
class QLabel;
class CVImage;

/**
 * @brief The MediaError enum provides the error types
 */
enum class MediaError {
	NO_ERROR, ///< no error
	UNEXSITED_SOURCE, ///< the source is not exsited
	/**
	 * @brief VEDIO_ONLY means the video is only
	 * @note  SOUND_ONLY means the partial displays
	 */
	VEDIO_ONLY,

	/**
	 * @brief SOUND_ONLY means the sound is only
	 * @note  SOUND_ONLY means the partial displays
	 */
	SOUND_ONLY,

	UNSUPPORT_SOURCE, ///< the source is not support
};

namespace MediaPlayerPublicSettings {
/**
 * @brief MisSyncDelay_t is the type of the delay
 * @note for some cases, it is rather accpetable for the mismatch
 */
using MisSyncDelay_t = unsigned int;

/**
 * @brief DEF_ACCPET_DELAY max delay we can accept
 */
static constexpr MisSyncDelay_t DEF_ACCPET_DELAY = 500;
};

/**
 * @brief The MediaInfo struct provides the media information
 * @note this is the meta data of the media
 */
struct MediaInfo {
	QString title; ///< the title of the media
	QString author; ///< the author of the media
	QString albumTitle; ///< the album title of the media
	QString albumArtist; ///< the album artist of the media
	QString composer; ///< the composer of the media
	QString genre; ///< the genre of the media
	qint64 durationMs; ///< the duration of the media
	QString date; ///< the date of the media

	int trackNumber; ///< the track number of the media
	int audioBitRate; ///< the audio bit rate of the media
	QString audioCodec; ///< the audio codec of the media
	QString mediaType; ///< the media type of the media
	int sampleRate; ///< the sample rate of the media
	QString publisher; ///< the publisher of the media
	QImage coverImage; ///< the cover image of the media
};

/**
 *  @brief MediaPlayer is the wrapper of
 *  VideoPlayer and AudioPlayer, with the
 *  sync of video and audio basically
 *  @note Author here in 2025.5.10
 * In Current Version, Only OpenCV is supported for the video play
 * and the audio is only supported by QMediaPlayer, with current
 * ALSA is used for the audio play in IMX6ULL, so for cross compilers
 * you must cross compile with ALSA support
 */
class MediaPlayer : public QObject {
	Q_OBJECT
public:
	/**
	 * @brief The MediaPlayerStatus class
	 * measures the status of the media player
	 */
	struct MediaPlayerStatus {
		/* media status */
		bool audio_ready { false }; ///< audio ready
		bool video_ready { false }; ///< video ready
		/* What has been fucking happened */
		QString video_discriptions {}; ///< video discriptions
		QString audio_discriptions {}; ///< audio discriptions
	};

	explicit MediaPlayer(QObject* parent = nullptr);
	Q_DISABLE_COPY(MediaPlayer);

	/**
	 * @brief setSource set the source of the media
	 * @param local_file the local file to open
	 * @note this actually bind the media we operate
	 */
	void setSource(const char* local_file);
	/**
	 * @brief source get the source of the media
	 * @return the source of the media
	 */
	QString source() const;

	/**
	 * @brief setVolume set the volume of the media
	 * @param percentage the percentage of the volume
	 * @note this is the percentage of the volume, not the value that
	 * without %, that is, the value should be between 0 and 1, not 0 and 100!
	 */
	void setVolume(const float percentage);
	/**
	 * @brief volume get the volume of the media
	 * @return the volume of the media
	 * @note this is the percentage of the volume, not the value that
	 * without %, that is, the value should be between 0 and 1, not 0 and 100!
	 */
	float volume() const;
	/**
	 * @brief get_durations get the durations of the media
	 * @return the durations of the media
	 */
	inline qint64 get_durations() const { return durations; }

	/**
	 * @brief get_position get the position of the media
	 * @return the position of the media
	 */
	inline qint64 get_position() const { return position; }

	/**
	 * @brief resume start the media player
	 * @return true if the media resume OK
	 * @note start the display if, the source is displayable and source is ready
	 */
	bool resume();

	/**
	 * @brief pause pause the media player
	 * @return true if the media pause OK
	 */
	bool pause();

	/**
	 * @brief close close the media player
	 * @return true if the media close OK
	 * @note close will release the media sources
	 * will pause don't, whom, just simply hang the media
	 */
	bool close();

	/**
	 * @brief isPlaying check if the media is playing
	 * @return true if the media is playing
	 * @note see if the audio is playing thus for default,
	 * if one is playing, the mediaplayer is playing :)
	 */
	bool isPlaying() const;

	/**
	 * @brief set_accept_missync_msecond set the default mis sync tolerance
	 * @param msec the msecond to accept
	 */
	inline void set_accept_missync_msecond(
		const unsigned int msec
		= MediaPlayerPublicSettings::DEF_ACCPET_DELAY) {
		mis_sync_seconds = msec;
	}

	/**
	 * @brief set_position moves to the target positions of the media
	 * @param position the position to set
	 */
	void set_position(const qint64 position);
signals:
	/**
	 * @brief display_frame display the frame by hooking this signals
	 * @param image the image to display
	 * @note for those who expect to use callback shell
	 * get the image, this image is the image you should display
	 * query from media underlevel
	 */
	void display_frame(QImage image);
	/* volumn changed signals */

	/** @brief volumeChanged the signal indicating the volume changed
	 * @param percentage the percentage of the volume
	 * @note this is the percentage of the volume, not the value that
	 * without %, that is, the value should be between 0 and 1, not 0 and 100!
	 */
	void volumeChanged(float percentage);

	/**
	 * @brief sourceOpened the signal indicating the source opened
	 * @param source the source of the media
	 * @param status the status of the media
	 */
	void sourceOpened(const QString source, ///< At which sources
					  MediaPlayer::MediaPlayerStatus status); ///< for what errors

	/**
	 * @brief videoAvailable for mp4 like video, this means we
	 * can display the medias
	 * @param sourceAvailable the source is available
	 * @param firstPage the first page of the media for display
	 */
	void videoAvailable(bool sourceAvailable, const QImage firstPage);

	/**
	 * @brief mediaEnd the signal indicating the media end
	 */
	void mediaEnd();
	/**
	 * @brief durationChanged the signal indicating the duration changed
	 * @param new_durantion the new duration of the media
	 */
	void durationChanged(qint64 new_durantion);

	/**
	 * @brief positionChanged the signal indicating the position changed
	 * @param position the new position of the media
	 */
	void positionChanged(qint64 position);

	/**
	 * @brief metaDataAvailable the signal indicating the meta data available
	 * @param info the meta data of the media
	 */
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

	/**
	 * @brief process_sync process the sync of the media between audio and video
	 * @param current_frame the current frame of the media
	 * @note this is the sync function, for most cases in IMX6ULL Alpha board,
	 * without ffmpeg hard decorder of video flow(as no chips support)
	 * things got fucking stuff (written in 2025.5.10 :(  )
	 */
	void process_sync(const CVImage& current_frame);
	void handle_sync_duration(qint64 durations);
	void handle_sync_position(qint64 position);
	void extract_metainfo();
};

#endif // MEDIAPLAYER_H
