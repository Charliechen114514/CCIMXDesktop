#include "QtAdaptTools.h"
#include "CVImage.h"
#include "CVImagePrivateOpencvImp.h"
QImage QtAdaptTools::toQImage(const CVImage& image) {
    cv::Mat raw_image = dynamic_cast<CVImageOpencvImpl*>(image.impl_ptr())->raw_image;

    if (raw_image.channels() == 1) {
        return QImage(
                   raw_image.data,
                   raw_image.cols,
                   raw_image.rows,
                   static_cast<int>(raw_image.step),
                   QImage::Format_Grayscale8)
            .copy();
    } else {
        return QImage(
                   raw_image.data,
                   raw_image.cols,
                   raw_image.rows,
                   static_cast<int>(raw_image.step),
                   QImage::Format_RGB888)
            .copy();
    }
}

QImage QtAdaptTools::toDisplayableImage(const CVImage& cvImage) {
    cv::Mat raw_image = dynamic_cast<CVImageOpencvImpl*>(cvImage.impl_ptr())->raw_image;

    if (raw_image.channels() == 1) {
        return toQImage(cvImage);
    } else {
        cv::cvtColor(raw_image, raw_image, cv::COLOR_BGR2RGB);
        return QImage(
                   raw_image.data,
                   raw_image.cols,
                   raw_image.rows,
                   static_cast<int>(raw_image.step),
                   QImage::Format_RGB888)
            .copy();
    }
}

CVImage QtAdaptTools::fromRGBQImage(const QImage& image) {
    QImage converted = image.convertToFormat(QImage::Format_RGB888);
    cv::Mat tmp(converted.height(), converted.width(), CV_8UC3,
                const_cast<uchar*>(converted.bits()),
                static_cast<size_t>(converted.bytesPerLine()));

    cv::Mat mat = tmp.clone();
    cv::cvtColor(mat, mat, cv::COLOR_RGB2BGR);

    CVImage cvimage;
    CVImageOpencvImpl* impl = dynamic_cast<CVImageOpencvImpl*>(cvimage.impl_ptr());
    impl->raw_image = mat;
    return cvimage;
}
