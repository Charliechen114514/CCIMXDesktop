#ifndef CVIMAGEPRIVATEOPENCVIMP_H
#define CVIMAGEPRIVATEOPENCVIMP_H
/* Here placed the common dependency files */
#include "CVImageImpl.h"
#include <opencv2/opencv.hpp>

class CVImageOpencvImpl : public CVImageImpl {
public:
	cv::Mat raw_image;

	/**
	 * @brief load_from_file loads the image from file
	 * @param filename the file name to load
	 */
	void load_from_file(const char* filename) override;

	/**
	 * @brief assigned assigns the image to this image
	 * @param impl the image to assign
	 * @param req_copy if true, then copy the image
	 */
	void assigned(const CVImageImpl* impl, bool req_copy) override;

	/**
	 * @brief pass_copy makes a passing assigned, for OpenCV like
	 * it just increase the ref count
	 * @param copied
	 */
	void pass_copy(const CVImageImpl* copied) override;

	/**
	 * @brief image_valid check if the image is valid
	 * @return true if the image is valid
	 */
	bool image_valid() override {
		return !raw_image.empty();
	}
};

#endif // CVIMAGEPRIVATEOPENCVIMP_H
