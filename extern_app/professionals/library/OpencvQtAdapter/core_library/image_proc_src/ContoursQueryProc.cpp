#include "ContoursQueryProc.h"
#include "CVImage.h"
#include "image_proc_opencv_impl/OpenCV_ProcessAdapter.h"
bool ContoursQueryProc::process(CVImage& prev_image) {
    CVImage image;
    image.assigned(prev_image, true);
    canny_processor.process(image);
    int code = 0;
    switch (method) {
    case Processor::ContoursQuery::Method::CHAIN_APPROX_NONE:
        code++;
    case Processor::ContoursQuery::Method::CHAIN_APPROX_SIMPLE:
        code++;
    case Processor::ContoursQuery::Method::CHAIN_APPROX_TC89_L1:
        code++;
    case Processor::ContoursQuery::Method::CHAIN_APPROX_TC89_KCOS:
        code++;
        break;
    }

    OpenCV_ProcessAdapter::processContoursDrawSession(prev_image.impl_ptr(), image.impl_ptr(), code);
    return true;
}
