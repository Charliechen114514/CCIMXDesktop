#include "CannyProcessor.h"
#include "CVImage.h"
#include "image_proc_opencv_impl/OpenCV_ProcessAdapter.h"
bool CannyProcessor::process(CVImage& prev_image) {
    gray.process(prev_image);
    blur.process(prev_image);
    OpenCV_ProcessAdapter::processCannyDetection(prev_image.impl_ptr(), threholds_pair.first, threholds_pair.second);
    return true;
}
