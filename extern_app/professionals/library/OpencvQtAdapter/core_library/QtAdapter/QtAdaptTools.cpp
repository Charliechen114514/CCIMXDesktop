#include "QtAdaptTools.h"
#include "CVImage.h"
#include "CVImagePrivateOpencvImp.h"
QImage QtAdaptTools::toQImage(const CVImage& image) {
	cv::Mat raw_image = dynamic_cast<CVImageOpencvImpl*>(image.impl_ptr())->raw_image;
    /* convert the raw image to QImage */
	return QImage(
        raw_image.data,
        raw_image.cols,
        raw_image.rows,
        static_cast<int>(raw_image.step[0]),
        QImage::Format_RGB888);
}

QImage QtAdaptTools::toDisplayableImage(const CVImage& cvImage) {
    cv::Mat raw_image = dynamic_cast<CVImageOpencvImpl*>(cvImage.impl_ptr())->raw_image;
    cv::cvtColor(raw_image, raw_image, cv::COLOR_BGR2RGB);
    /* convert the raw image to QImage */
    return QImage(
        raw_image.data,
        raw_image.cols,
        raw_image.rows,
        static_cast<int>(raw_image.step[0]),
        QImage::Format_RGB888);
}
