#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H
#include "CVImage.h"
#include "VideoPlayerImpl.h"
#include <QObject>
#include <QTimer>
/* Video Support is limited to OpenCV Due to the RealTime Request */
namespace cv {
class VideoCapture;
};

/**
 * @brief VideoPlayerTools provides the tools for video player
 *
 */
namespace VideoPlayerTools {

/**
 * @brief frame_to_mseconds convert the frame to mseconds
 * @param frame the frame to convert
 * @param fps the fps of the video
 * @return the mseconds
 */
qint64 frame_to_mseconds(int frame, int fps);

/**
 * @brief mseconds_to_frame convert the mseconds to frame
 * @param msec the mseconds to convert
 * @param fps the fps of the video
 * @return the frame
 */
qint64 mseconds_to_frame(qint64 msec, int fps);
}

class VideoPlayer : public QObject {
	Q_OBJECT
public:
	explicit VideoPlayer(QObject* parent = nullptr);
	~VideoPlayer();

	/**
	 * @brief open open the video file
	 * @param video_path the video path to open
	 * @return true if the video is opened successfully
	 */
	bool open(const char* video_path);

	/**
	 * @brief current_handle get the current handle
	 * @return the current handle
	 */
	QString current_handle() const { return last_open; }

	/**
	 * @brief close close the video file
	 * @return  true if the video is closed successfully
	 */
	bool close();

	/**
	 * @brief play start the video play
	 * @return true if the video is played successfully
	 */
	bool play();

	/**
	 * @brief pause stop the video play
	 * @return true if the video is paused successfully
	 */
	bool pause();
	/* get the total frame */

	/**
	 * @brief total_frame get the total frame of the video
	 * @return the total frame of the video
	 */
	int total_frame() const;

	/**
	 * @brief total_msecs get the total mseconds of the video
	 * @return the total mseconds of the video
	 */
	inline int total_msecs() const {
		return VideoPlayerTools::frame_to_mseconds(
			total_frame(), info.fps);
	}

	/**
	 * @brief get_info get the info of the video
	 * @return the info of the video, including frame info, fps like and so on
	 */
	inline VideoPlayerInfo get_info() const { return info; }
	/**
	 * @brief current_frame get the current frame of the video
	 * @return the current frame of the video
	 */
	int current_frame() const;

	/**
	 * @brief valid_video check if the video is valid
	 * @return true if the video is valid
	 */
	bool valid_video() const;

	/**
	 * @brief is_playing check if the video is playing
	 * @return true if the video is playing
	 */
	bool is_playing() const;

	/**
	 * @brief currentFrameMSec get the current frame in mseconds
	 * @return the current frame in mseconds
	 */
	qint64 currentFrameMSec() const;

	/**
	 * @brief setCurrentFrameMSec set the current frame in mseconds
	 * @param msec the mseconds to set
	 * @return  true if the mseconds is set successfully
	 */
	bool setCurrentFrameMSec(const qint64 msec);

	/**
	 * @brief escapeFrame escape the current frame
	 * @note this will escape only one frame, if you wanna
	 * escape frames, use for loops
	 */
	void escapeFrame();

	/**
	 * @brief peekFrame peek the frame of the video
	 * @param container the container to store the frame
	 * @param frame_request the frame requested
	 * @return  true if the frame is peeked successfully
	 */
	bool peekFrame(CVImage& container, int frame_request);
signals:
	/**
	 * @brief openError the signal indicating the open error
	 * @param error the error code
	 */
	void openError(const VideoPlayerOpenErrorCode error);

	/**
	 * @brief frameReady the signal indicating the frame is ready
	 * @param image the image to display
	 * @note the request will send the image waiting display
	 */
	void frameReady(const CVImage image);

	/**
	 * @brief about_fetch_frame the signal indicating the frame is ready
	 */
	void about_fetch_frame();

	/**
	 * @brief videoEnd the signal indicating the video end
	 */
	void videoEnd();

private slots:
	/**
	 * @brief time_to_fetch_next_frame the slot to fetch the next frame
	 */
	void time_to_fetch_next_frame();

private:
	VideoPlayerImpl* impl { nullptr }; ///< the video player impl
	bool on_play { false }; ///< the state of video play
	VideoPlayerInfo info; ///< video player info
	int play_sleep { 0 }; ///< the sleep time for next frame fetch
	QString last_open {}; ///< cached handling source places
};

#endif // VIDEOPLAYER_H
