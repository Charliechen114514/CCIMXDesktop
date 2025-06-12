#include "FaceDetector.h"
#include "CVImage.h"
#include "image_proc_opencv_impl/OpenCV_ProcessAdapter.h"
void FaceDetector::detectFaces(CVImage& blank, const CVImage& src) {
    OpenCV_ProcessAdapter::draw_faces(blank.impl_ptr(), src.impl_ptr());
}
