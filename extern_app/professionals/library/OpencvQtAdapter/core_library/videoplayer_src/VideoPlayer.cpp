#include "VideoPlayer.h"

VideoPlayer::VideoPlayer(QObject* parent)
	: QObject { parent } {
	impl = VideoPlayerImplFactory::request_impl();
	/* when timeout, we need to fetch a frame */
}

VideoPlayer::~VideoPlayer() {
	delete impl;
}

bool VideoPlayer::open(const char* video_path) {
	VideoPlayerOpenErrorCode error_code;
	if (!impl->open(video_path, error_code)) {
		/* openError emit the error handle async */
		emit openError(error_code);
		return false;
	}
	/* fetch the info for once */
	info = impl->current_video_info();
	/* thus, we can set the timer interval for the 1s shot */
	play_sleep = 1000 / info.fps;
	return true;
}

bool VideoPlayer::close() {
	if (impl->isOpened()) {
		impl->close();
	}
	return true;
}

bool VideoPlayer::play() {
	if (!impl->isOpened()) {
		/* thus the video is not opened */
		return false;
	}

	if (on_play) {
		/* thus the video is already playing */
		return false;
	}
	on_play = true;
	/* invoke frame fetch at once */
	QTimer::singleShot(0, this, &VideoPlayer::time_to_fetch_next_frame);
	return true;
}

bool VideoPlayer::pause() {

	if (!impl->isOpened()) {
		/* thus the video is not opened */
		return false;
	}

	if (!on_play) {
		/* thus the video is already paused */
		return false;
	}

	on_play = false;
	return true;
}

int VideoPlayer::total_frame() const {
	return impl->total_frame();
}

int VideoPlayer::current_frame() const {
	return impl->total_frame() - impl->current_frame();
}

bool VideoPlayer::valid_video() const {
	return impl->isOpened();
}

qint64 VideoPlayer::currentFrameMSec() const {
	if (!impl->isOpened()) {
		/* thus the video is not opened */
		return 0;
	}

	if (info.fps <= 0)
		return 0;
	return static_cast<qint64>(1000.0 * impl->current_frame() / info.fps);
}

void VideoPlayer::escapeFrame() {
	if (!impl->isOpened()) {
		/* thus the video is not opened */
		return;
	}

	if (!on_play) {
		/* thus the video is not playing */
		return;
	}

	if (impl->current_frame() >= impl->total_frame()) {
		/* thus the video is already finished */
		return;
	}
	/* escape the frame */
	impl->escapeFrame();
}

/* Time out calls this  */
void VideoPlayer::time_to_fetch_next_frame() {

	if (!on_play) {
		/*
		 * thus we are not playing, this is the
		 * final old invoke, return fast!
		 */
		return;
	}

	/* About to fetch the frame signals */
	emit about_fetch_frame();

	/* fetch the frame */
	CVImage image;
	if (impl->rollto_nextFrame(image)) {
		/* frame ready to display */
		emit frameReady(image);
	} else {
		on_play = false;
	}
	/* thus a next frame is about to come ... */
	QTimer::singleShot(play_sleep, this, &VideoPlayer::time_to_fetch_next_frame);
}
