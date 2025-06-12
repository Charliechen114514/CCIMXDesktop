#include "HistCreator.h"
#include "CVImage.h"
#include "image_proc_opencv_impl/OpenCV_ProcessAdapter.h"
void HistCreator::filled_hist(CVImage& blank, const CVImage& src) {
    OpenCV_ProcessAdapter::generate_hist(blank.impl_ptr(), src.impl_ptr());
}
