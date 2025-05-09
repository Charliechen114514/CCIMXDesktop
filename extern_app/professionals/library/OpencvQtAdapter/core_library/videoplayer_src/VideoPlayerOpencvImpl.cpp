#include "VideoPlayerOpencvImpl.h"
#include "CVImagePrivateOpencvImp.h"
#include <opencv2/videoio.hpp>

namespace {

inline bool isHandleValid(cv::VideoCapture* cap) {
	return cap;
}

inline bool isHandleOpened(cv::VideoCapture* cap) {
	return cap && cap->isOpened();
}

}

VideoPlayerOpencvImpl::VideoPlayerOpencvImpl() {
	internal_capture = new cv::VideoCapture;
}

VideoPlayerOpencvImpl::~VideoPlayerOpencvImpl() {
	if (internal_capture) {
		internal_capture->release();
	}
	delete internal_capture;
}

int VideoPlayerOpencvImpl::total_frame() const {

	if (!isHandleOpened(internal_capture)) {
		return INVALID_VIDEO_FRAME_N;
	}

	return internal_capture->get(cv::CAP_PROP_FRAME_COUNT);
}

int VideoPlayerOpencvImpl::current_frame() {
	if (!isHandleOpened(internal_capture)) {
		return INVALID_VIDEO_FRAME_N;
	}

	return internal_capture->get(cv::CAP_PROP_POS_FRAMES);
}

/* rolling to the next frame with the CVImage returns */
bool VideoPlayerOpencvImpl::rollto_nextFrame(CVImage& container) {

	if (!isHandleOpened(internal_capture)) {
		return false;
	}

	CVImageOpencvImpl* cvImpl = dynamic_cast<CVImageOpencvImpl*>(container.impl_ptr());
	if (!cvImpl)
		return false; /* uncorrect and unlikely happens */
	return internal_capture->read(cvImpl->raw_image);
}

bool VideoPlayerOpencvImpl::peek_frame(CVImage& container, int frame_request) {
	if (!isHandleOpened(internal_capture)) {
		return false;
	}

	CVImageOpencvImpl* cvImpl = dynamic_cast<CVImageOpencvImpl*>(container.impl_ptr());
	if (!cvImpl)
		return false; /* uncorrect and unlikely happens */

	/* reject unopened handle */
	if (!isHandleOpened(internal_capture)) {
		return false;
	}

	if (frame_request < 0 || frame_request >= total_frame()) {
		/* request overflow */
		return false;
	}

	/* request the current frame */
	int current_tmp = current_frame();

	/* set to the request frame */
	if (!internal_capture->set(cv::CAP_PROP_POS_FRAMES, frame_request)) {
		/* request failure */
		return false;
	}

	if (!internal_capture->read(cvImpl->raw_image)) {
		/* Make an attempataions to roll back */
		internal_capture->set(cv::CAP_PROP_POS_FRAMES, current_tmp);
		return false;
	}

	internal_capture->set(cv::CAP_PROP_POS_FRAMES, current_tmp);
	return true;
}

VideoPlayerInfo VideoPlayerOpencvImpl::current_video_info() const {
	if (!isHandleOpened(internal_capture)) {
		return {};
	}

	return {
		static_cast<int>(internal_capture->get(cv::CAP_PROP_FPS)),
		static_cast<int>(internal_capture->get(cv::CAP_PROP_FRAME_WIDTH)),
		static_cast<int>(internal_capture->get(cv::CAP_PROP_FRAME_HEIGHT))
	};
}

bool VideoPlayerOpencvImpl::open(const char* filename, VideoPlayerOpenErrorCode& error_code) {

	if (isHandleOpened(internal_capture)) {
		error_code = VideoPlayerOpenErrorCode::DupOpen;
		return false;
	}

	if (!internal_capture->open(filename)) {
		error_code = VideoPlayerOpenErrorCode::FileUnExsited;
		return false;
	}

	error_code = VideoPlayerOpenErrorCode::NoError;
	return true;
}

void VideoPlayerOpencvImpl::close() {
	if (isHandleOpened(internal_capture)) {
		internal_capture->release();
	}
}

bool VideoPlayerOpencvImpl::isOpened() const {
	if (isHandleOpened(internal_capture)) {
		return true;
	}
	return false;
}

void VideoPlayerOpencvImpl::escapeFrame() {
	internal_capture->grab();
	internal_current_frame++;
}

VideoPlayerImpl* VideoPlayerImplFactory::request_impl() {
	return new VideoPlayerOpencvImpl;
}
