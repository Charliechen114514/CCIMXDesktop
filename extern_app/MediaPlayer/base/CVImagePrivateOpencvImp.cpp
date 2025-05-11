#include "CVImagePrivateOpencvImp.h"
#include "CVImage.h"
#include "CVImageImpl.h"
#include "CVTools.h"

void CVImageOpencvImpl::load_from_file(const char* filename) {
	/* read from the file */
	raw_image = cv::imread(filename);
}

void CVImageOpencvImpl::assigned(
	const CVImageImpl* impl, bool req_copy) {
	const CVImageOpencvImpl* opencv_impl
		= dynamic_cast<
			const CVImageOpencvImpl*>(impl);
	if (!opencv_impl)
		return; /* unlikely */
	if (req_copy) {
		/* copy to assigned */
		opencv_impl->raw_image.copyTo(raw_image);
	} else {
		raw_image = opencv_impl->raw_image;
	}
}

void CVImageOpencvImpl::pass_copy(const CVImageImpl* copied) {
	const CVImageOpencvImpl* copied_cor
		= dynamic_cast<
			const CVImageOpencvImpl*>(copied);
	if (!copied_cor)
		return; /* unlikely */
	raw_image = copied_cor->raw_image;
}

namespace CVTools {

void display(const CVImage& image, const DisplayParams& params) {
	CVImageOpencvImpl* impl = dynamic_cast<CVImageOpencvImpl*>(image.impl_ptr());
	if (!impl)
		return;
	cv::namedWindow(params.name, cv::WINDOW_NORMAL);
	cv::resizeWindow(
		params.name,
		params.window_size.first,
		params.window_size.second);

	cv::imshow(params.name, impl->raw_image);

	cv::waitKey(params.waitTime);
}

} /* Thus CVTools definitions end */
