#include "CVImage.h"
#include "CVImageImpl.h"

CVImage::CVImage() {
	private_handle = CVImageImplFactory::target_impl();
}

CVImage::CVImage(const CVImage& image) {
	private_handle = CVImageImplFactory::target_impl();
	/* count assigned the image */
	private_handle->pass_copy(image.private_handle);
}

const CVImage& CVImage::
operator=(const CVImage& image) {
	if (&image == this) {
		return *this;
	}
	private_handle = CVImageImplFactory::target_impl();
	/* count assigned the image */
	private_handle->pass_copy(image.private_handle);
	return *this;
}

CVImage::~CVImage() {
	delete private_handle;
}

void CVImage::loadFile(const char* filename) {
	private_handle->load_from_file(filename);
}

void CVImage::assigned(const CVImage& image,
					   bool load_as_copy) {
	private_handle->assigned(image.private_handle, load_as_copy);
}
