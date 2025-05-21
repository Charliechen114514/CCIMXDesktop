#ifndef CVIMAGE_H
#define CVIMAGE_H
#include "CVImageImpl.h"

class CVImage {
public:
	/* Friend class are assigned for direct visit */
	CVImage();
	CVImage(const CVImage& image);
	const CVImage& operator=(const CVImage& image);
	~CVImage();

	/* load as file */
	void loadFile(const char* filename);
	void assigned(
		const CVImage& image, /* other copy */
		bool load_as_copy = false /* req to copy */
	);

	inline bool image_valid() const { return private_handle->image_valid(); }
	inline CVImageImpl* impl_ptr() const { return private_handle; }

private:
	CVImageImpl* private_handle { nullptr };
};

#endif // CVIMAGE_H
