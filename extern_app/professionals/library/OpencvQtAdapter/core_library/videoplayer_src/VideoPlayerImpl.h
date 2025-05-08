#ifndef VIDEOPLAYERIMPL_H
#define VIDEOPLAYERIMPL_H
#include "CVImage.h"
#include <QString>
static constexpr short INVALID_VIDEO_FRAME_N = -1;

enum class VideoPlayerOpenErrorCode {
	NoError,
	DupOpen,
	FileUnExsited
};

struct VideoPlayerInfo {
	int fps;
	int width;
	int height;
};

class VideoPlayerImpl {
public:
	VideoPlayerImpl() = default;
	virtual ~VideoPlayerImpl() = default;
	/*
	 *	Copy is not acceptable for video
	 */
	Q_DISABLE_COPY(VideoPlayerImpl);
	/* For Video Impl Classes, these are expected to finish */
	/* data interfaces */
	/* current video owns frame waiting for display */
	virtual int total_frame() const = 0;
	virtual int current_frame() = 0;
	/*
	 * CVImage interface is expected to handle image processing
	 */
	/*
	 * peek the frame sync,
	 * with the video is supposed to roll the next level
	 */
	virtual bool rollto_nextFrame(CVImage& container) = 0;
	/* the video will not be rolled,
	 * and the target frame will be request and if success,
	 * install to the container
	 */
	virtual bool peek_frame(CVImage& container, int frame_request) = 0;
	/* for upper level widgets, we need to get from the info */
	virtual VideoPlayerInfo current_video_info() const = 0;

	/*
	 *	Function interfaces
	 *		open: makes the resources available
	 *		close: disabled the resources, shutdown this
	 */
	virtual bool open(const char* filename, VideoPlayerOpenErrorCode& error_code) = 0;
	virtual bool isOpened() const = 0;
	virtual void close() = 0;
};

/* for upper level VideoPlayer,
 * these is expected to be used for fetching
 */
class VideoPlayerImplFactory {
public:
    static VideoPlayerImpl* request_impl();
};

#endif // VIDEOPLAYERIMPL_H
