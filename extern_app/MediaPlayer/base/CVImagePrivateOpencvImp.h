#ifndef CVIMAGEPRIVATEOPENCVIMP_H
#define CVIMAGEPRIVATEOPENCVIMP_H
/* Here placed the common dependency files */
#include "CVImageImpl.h"
#include <opencv2/opencv.hpp>

class CVImageOpencvImpl : public CVImageImpl {
public:
	cv::Mat raw_image;
	void load_from_file(const char* filename) override;
	void assigned(const CVImageImpl* impl, bool req_copy) override;
	void pass_copy(const CVImageImpl* copied) override;
	bool image_valid() override {
		return !raw_image.empty();
	}
};

#endif // CVIMAGEPRIVATEOPENCVIMP_H
