#include "GrayProcessor.h"
#include "CVImage.h"
#include "CVImagePrivateOpencvImp.h"
#include "image_proc_opencv_impl/OpenCV_ProcessAdapter.h"
GrayProcessor::GrayProcessor()
    : ImageProc() {
}

bool GrayProcessor::process(CVImage& prev_image) {
    OpenCV_ProcessAdapter::grayImage(prev_image.impl_ptr(),
                                     cv::COLOR_BGR2GRAY);
    return true;
}
