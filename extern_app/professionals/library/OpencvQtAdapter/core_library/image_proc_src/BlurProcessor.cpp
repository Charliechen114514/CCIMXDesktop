#include "BlurProcessor.h"
#include "CVImage.h"
#include "image_proc_opencv_impl/OpenCV_ProcessAdapter.h"

MeanBlur::MeanBlur()
    : BlurProcessor(HandleType::MeanBlur) { }

bool MeanBlur::process(CVImage& prev_image) {
    return process(prev_image, package);
}

bool MeanBlur::process(CVImage& prev_image, const MeanBlurPackage& package) {
    OpenCV_ProcessAdapter::processBlurType(prev_image.impl_ptr(), package.kernel_size);
    return true;
}

GuassainBlur::GuassainBlur()
    : BlurProcessor(HandleType::GuassainBlur) {
}

bool GuassainBlur::process(CVImage& prev_image) {
    return process(prev_image, package);
}

bool GuassainBlur::process(
    CVImage& prev_image, const GaussainPackage& package) {
    OpenCV_ProcessAdapter::processGaussainBlurType(
        prev_image.impl_ptr(), package.kernel_size,
        package.sigma_x, package.sigma_y);
    return true;
}

MedianBlur::MedianBlur()
    : BlurProcessor(HandleType::MedianBlur) {
}

bool MedianBlur::process(CVImage& prev_image) {
    return process(prev_image, package);
}

bool MedianBlur::process(CVImage& prev_image, const MedianBlurPackage& package) {
    OpenCV_ProcessAdapter::processMedianBlurType(prev_image.impl_ptr(), package.kernel_size);
    return true;
}

FilterBlur::FilterBlur()
    : BlurProcessor(HandleType::FilterBlur) {
}

bool FilterBlur::process(CVImage& prev_image) {
    return process(prev_image, package);
}

bool FilterBlur::process(CVImage& prev_image, const FilterPackage& package) {
    OpenCV_ProcessAdapter::processFilterBlurType(prev_image.impl_ptr(), package.d,
                                                 package.sigma_space, package.sigma_color);
    return true;
}
