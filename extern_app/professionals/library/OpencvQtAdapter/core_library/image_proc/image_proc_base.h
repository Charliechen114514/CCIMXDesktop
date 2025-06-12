#ifndef IMAGE_PROC_BASE_H
#define IMAGE_PROC_BASE_H
class CVImage;
/**
 * @brief base of all processors
 * 
 */
struct ImageProc {
	/**
	 * @brief Construct a new Image Proc object
	 * 
	 */
	ImageProc() = default;
	virtual ~ImageProc() = default;
	/**
	 * @brief process images
	 * 
	 * @param prev_image 
	 * @return whether success
	 */
	virtual bool process(CVImage& prev_image) = 0;
};

#endif // IMAGE_PROC_BASE_H
