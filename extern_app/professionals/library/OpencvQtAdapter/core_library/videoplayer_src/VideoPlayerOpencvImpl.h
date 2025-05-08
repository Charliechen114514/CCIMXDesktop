#ifndef VIDEOPLAYEROPENCVIMPL_H
#define VIDEOPLAYEROPENCVIMPL_H
#include "VideoPlayerImpl.h"
namespace cv {
class VideoCapture;
}

class VideoPlayerOpencvImpl : public VideoPlayerImpl {
public:
	VideoPlayerOpencvImpl();
	~VideoPlayerOpencvImpl() override;
	int total_frame() const override;
	int current_frame() override;
	bool rollto_nextFrame(CVImage& container) override;
	bool peek_frame(CVImage& container, int frame_request) override;
	VideoPlayerInfo current_video_info() const override;
	bool open(const char* filename,
			  VideoPlayerOpenErrorCode& error_code) override;
	void close() override;
	bool isOpened() const override;

private:
	cv::VideoCapture* internal_capture { nullptr };
	int internal_current_frame { INVALID_VIDEO_FRAME_N };
};

#endif // VIDEOPLAYEROPENCVIMPL_H
