#ifndef CVIMAGE_H
#define CVIMAGE_H
#include "CVImageImpl.h"

/**
 * @brief The CVImage class is the image class
 * that provides the image in the frameworks
 */
class CVImage {
public:
	CVImage(); ///< defines the default constructor
	CVImage(const CVImage& image); ///< copy constructor
	const CVImage& operator=(const CVImage& image); ///< copy assignment
	~CVImage(); ///< destructor

	/* load as file */

	/**
	 * @brief loadFile loads the file into the image
	 * @param filename the file name to load
	 */
	void loadFile(const char* filename);

	/**
	 * @brief assigned assigns the image to this image
	 * @param image the image to assign
	 * @param load_as_copy if true, then copy the image
	 */
	void assigned(
		const CVImage& image, /* other copy */
		bool load_as_copy = false /* req to copy */
	);

	/**
	 * @brief assigned assigns the image to this image
	 */
	inline bool image_valid() const { return private_handle->image_valid(); }

	/**
	 * @brief impl_ptr get the impl pointer
	 * @return the impl pointer
	 */
	inline CVImageImpl* impl_ptr() const { return private_handle; }

private:
	CVImageImpl* private_handle { nullptr }; ///< the private handle
};

#endif // CVIMAGE_H
