#ifndef VIDEOPLAYEROPENCVIMPL_H
#define VIDEOPLAYEROPENCVIMPL_H
#include "VideoPlayerImpl.h"
namespace cv {
class VideoCapture;
}

/**
 * @brief The VideoPlayerOpencvImpl class provides the
 * OpenCV implementation of the video player
 * @note this is the implementation of the video player
 */
class VideoPlayerOpencvImpl : public VideoPlayerImpl {
public:
	VideoPlayerOpencvImpl();
	~VideoPlayerOpencvImpl() override;

	/**
	 * @brief total_frame get the total frame of the video
	 * @return the total frame of the video
	 */
	int total_frame() const override;

	/**
	 * @brief current_frame get the current frame of the video
	 * @return the current frame of the video
	 */
	int current_frame() override;

	/**
	 * @brief rollto_nextFrame roll to the next frame
	 * @param container the container to store the frame
	 * @return true if the frame is rolled successfully
	 * @note this function should peek the frame sync,
	 */
	bool rollto_nextFrame(CVImage& container) override;

	/**
	 * @brief peek_frame peek the frame of the video
	 * @param container the container to store the frame
	 * @param frame_request the frame requested
	 * @return true if the frame is peeked successfully
	 * @note the video will not be rolled,
	 */
	bool peek_frame(CVImage& container, int frame_request) override;

	/**
	 * @brief current_video_info get the current video information
	 * @return the current video information
	 */
	VideoPlayerInfo current_video_info() const override;

	/**
	 * @brief	open open the video file
	 * @param	filename	the file name to open
	 * @param	error_code the error code
	 * @return	true if the video is opened successfully
	 */
	bool open(const char* filename,
			  VideoPlayerOpenErrorCode& error_code) override;

	/**
	 * @brief close close the video file
	 */
	void close() override;

	/**
	 * @brief isOpened check if the video is opened
	 * @return true if the video is opened
	 */
	bool isOpened() const override;

	/**
	 * @brief escapeFrame escape the current frame
	 * @note frame is supposed to abolished,
	 * pointer should be moved forward
	 */
	void escapeFrame() override;

	/**
	 * @brief jumpToFrame jump to the frame of the video
	 * @param frame_request the frame requested
	 * @note this function should jump to the frame sync,
	 */
	void jumpToFrame(int frame_request) override;

private:
	cv::VideoCapture* internal_capture { nullptr }; ///< the video capture handle
	int internal_current_frame { INVALID_VIDEO_FRAME_N }; ///< the current frame
};

#endif // VIDEOPLAYEROPENCVIMPL_H
