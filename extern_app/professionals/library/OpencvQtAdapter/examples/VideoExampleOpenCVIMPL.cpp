#include "core_library/cvimage/CVTools.h"
#include "core_library/videoplayer/VideoPlayerOpencvImpl.h"
#include <QThread>
#include <iostream>

void show_video_message(const VideoPlayerOpencvImpl& impl) {
	std::cout << "Video Info:" << std::endl;
	std::cout << "Width: " << impl.current_video_info().width << std::endl;
	std::cout << "Height: " << impl.current_video_info().height << std::endl;
	std::cout << "FPS: " << impl.current_video_info().fps << std::endl;
	std::cout << "Total Frame: " << impl.total_frame() << std::endl;
}

int main(int argc, char* argv[]) {
	const char* video_path = nullptr;
	if (argc < 2) {
		std::cout << "Provide less then 2 args, using default video" << std::endl;
		video_path = TEST_VIDEO_DIR "/test.mp4";
	} else {
		video_path = argv[1];
	}

	VideoPlayerOpencvImpl player;
	VideoPlayerOpenErrorCode error_code;
	player.open(video_path, error_code);
	if (!player.isOpened()) {
		std::cerr << "Invalid video data!" << std::endl;
		return 3;
	}
	show_video_message(player);
	CVImage image;
	CVTools::DisplayParams params;
	params.name = "Charlies CVImage";
	params.window_size = { 640, 480 };
	params.waitTime = 1000 / player.current_video_info().fps;

	while (player.rollto_nextFrame(image)) {
		CVTools::display(image, params);
	}
	return 0;
}
