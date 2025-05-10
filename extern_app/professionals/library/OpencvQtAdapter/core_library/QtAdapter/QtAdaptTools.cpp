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
