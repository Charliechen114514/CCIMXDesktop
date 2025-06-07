#include "OpenCV_ProcessAdapter.h"
#include "CVImagePrivateOpencvImp.h"
#include <opencv2/opencv.hpp>

void OpenCV_ProcessAdapter::grayImage(CVImageImpl* image_mat, int code) {
	CVImageOpencvImpl* impl = dynamic_cast<CVImageOpencvImpl*>(image_mat);
	cv::cvtColor(impl->raw_image, impl->raw_image, cv::COLOR_BGR2GRAY);
}
