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

namespace VideoPlayerTools {

};

class VideoPlayer : public QObject {
	Q_OBJECT
public:
	explicit VideoPlayer(QObject* parent = nullptr);
	~VideoPlayer();
	bool open(const char* video_path);
	bool close();
	/* for the pause video, resume is OK */
	bool play();
	/* hang the video display */
	bool pause();
	/* get the total frame */
	int total_frame() const;
	/* frame left for display */
	int current_frame() const;
	/* is current video valid */
	bool valid_video() const;
	/* is current video on play? */
	inline bool is_playing() const { return on_play; }
	/* compound for the audio-frame sync */
	qint64 currentFrameMSec() const;
	/* set current frame as mseconds */
	bool setCurrentFrameMSec(const qint64 msec);
	/* for the frame escape, then next frame will be abolished */
	void escapeFrame();

signals:
	/* error occurs */
	void openError(const VideoPlayerOpenErrorCode error);
	/* the request will send the image waiting display */
	void frameReady(const CVImage image);
	/* frame is about to fetch */
	void about_fetch_frame();

private slots:
	void time_to_fetch_next_frame();

private:
	VideoPlayerImpl* impl { nullptr };
	/*
	 * on_play handles the state of video play
	 */
	bool on_play { false };
	VideoPlayerInfo info;
	int play_sleep { 0 };
};

#endif // VIDEOPLAYER_H
