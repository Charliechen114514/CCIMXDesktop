#ifndef VIDEOPLAYERIMPL_H
#define VIDEOPLAYERIMPL_H
#include "CVImage.h"
#include <QString>
static constexpr short INVALID_VIDEO_FRAME_N = -1;

/**
 * @brief The VideoPlayerOpenErrorCode enum provides the error types
 * @note this is the error code for the video player
 */
enum class VideoPlayerOpenErrorCode {
	NoError, ///< no error
	DupOpen, ///< duplicate open
	FileUnExsited, ///< file unexsited
	OpenFailed, ///< open failed, with other reasons
};

/**
 * @brief The VideoPlayerInfo struct provides the video information
 * @note this is the meta data of the video
 */
struct VideoPlayerInfo {
	int fps;
	int width;
	int height;
};

/**
 * @brief The VideoPlayerImpl class VideoPlayerImpl is
 * the interface for video player
 * and the impl class is supposed to be used for the video player
 */
class VideoPlayerImpl {
public:
	/**
	 * @brief Construct a new Video Player Impl object
	 * 
	 */
	VideoPlayerImpl() = default;
	virtual ~VideoPlayerImpl() = default;
	/**
	 * @brief Copy is not acceptable for video
	 * 
	 */
	Q_DISABLE_COPY(VideoPlayerImpl);

	/* data interfaces */
	/* current video owns frame waiting for display */
	/**
	 * @brief total_frame get the total frame of the video
	 * @return the total frame of the video
	 */
	virtual int total_frame() const = 0;

	/**
	 * @brief current_frame get the current frame of the video
	 * @return the current frame of the video
	 */
	virtual int current_frame() = 0;

	/**
	 * @brief rollto_nextFrame roll to the next frame
	 * @param container the container to store the frame
	 * @return true if the frame is rolled successfully
	 * @note this function should peek the frame sync,
	 * with the video is supposed to roll the next level
	 */
	virtual bool rollto_nextFrame(CVImage& container) = 0;
	/**
	 * @brief peek_frame peek the frame of the video
	 * @param container the container to store the frame
	 * @param frame_request the frame requested
	 * @return true if the frame is peeked successfully
	 * @note the video will not be rolled,
	 * and the target frame will be request and if success,
	 * install to the container
	 */
	virtual bool peek_frame(CVImage& container, int frame_request) = 0;
	/**
	 * @brief current_video_info get the current video information
	 * @return the current video information
	 * @note for upper level widgets, we need to get from the info
	 */
	virtual VideoPlayerInfo current_video_info() const = 0;

	/**
	 * @brief escapeFrame escape the current frame
	 * @note frame is supposed to abolished,
	 * pointer should be moved forward
	 */
	virtual void escapeFrame() = 0;

	/**
	 * @brief jumpToFrame jump to the frame of the video
	 * @param frame_request the frame requested
	 * @note this function should jump to the frame sync,
	 */
	virtual void jumpToFrame(int frame_request) = 0;

	/*
	 *	Function interfaces
	 */

	/**
	 * @brief open open the video file
	 * @param filename the file name to open
	 * @param error_code the error code
	 * @return true if the video is opened successfully
	 * @note in syntax level, it means making the resources available
	 */
	virtual bool open(const char* filename, VideoPlayerOpenErrorCode& error_code) = 0;

	/**
	 * @brief isOpened check if the video is opened
	 * @return true if the video is opened
	 */
	virtual bool isOpened() const = 0;

	/**
	 * @brief close close the video file
	 * @note in syntax level, it means making the resources un-available
	 * (disabled the resources, shutdown this)
	 */
	virtual void close() = 0;
};

/**
 * @brief The VideoPlayerImplFactory class is the factory class
 * for the video player impl
 */
class VideoPlayerImplFactory {
public:
	/**
	 * @brief request_impl fetch the IMPL according platform/backend framework
	 * @return the target impl
	 */
	static VideoPlayerImpl* request_impl();
};

#endif // VIDEOPLAYERIMPL_H
