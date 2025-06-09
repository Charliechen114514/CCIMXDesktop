#include "OpenCV_ProcessAdapter.h"
#include "CVImagePrivateOpencvImp.h"
#include <opencv2/opencv.hpp>

void OpenCV_ProcessAdapter::grayImage(CVImageImpl* image_mat, int code) {
    CVImageOpencvImpl* impl = dynamic_cast<CVImageOpencvImpl*>(image_mat);
    cv::Mat result;
    cv::cvtColor(impl->raw_image, result, cv::COLOR_BGR2GRAY);
    impl->raw_image = result.clone();
}

void OpenCV_ProcessAdapter::processBlurType(CVImageImpl* image_mat, int kernel_size) {
    CVImageOpencvImpl* impl = dynamic_cast<CVImageOpencvImpl*>(image_mat);
    cv::Mat result;
    cv::blur(impl->raw_image, result, cv::Size(kernel_size, kernel_size));
    impl->raw_image = result.clone();
}

void OpenCV_ProcessAdapter::processGaussainBlurType(CVImageImpl* image_mat, int kernel_size, double sigma_x, double sigma_y) {
    CVImageOpencvImpl* impl = dynamic_cast<CVImageOpencvImpl*>(image_mat);
    cv::Mat result;
    cv::GaussianBlur(impl->raw_image, result, cv::Size(kernel_size, kernel_size), sigma_x, sigma_y);
    impl->raw_image = result.clone();
}

void OpenCV_ProcessAdapter::processMedianBlurType(CVImageImpl* image_mat, int kernel_size) {
    CVImageOpencvImpl* impl = dynamic_cast<CVImageOpencvImpl*>(image_mat);
    cv::Mat result;
    cv::medianBlur(impl->raw_image, result, kernel_size);
    impl->raw_image = result.clone();
}

void OpenCV_ProcessAdapter::processFilterBlurType(CVImageImpl* image_mat, int d, double sigma_color, double sigma_space) {
    CVImageOpencvImpl* impl = dynamic_cast<CVImageOpencvImpl*>(image_mat);
    cv::Mat result;
    cv::bilateralFilter(impl->raw_image, result, d, sigma_color, sigma_space);
    impl->raw_image = result.clone();
}
