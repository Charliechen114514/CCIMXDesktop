#ifndef CVIMAGEIMPL_H
#define CVIMAGEIMPL_H
/* class interfaces */

/**
 * @brief The CVImageImpl class is the image interface classes,
 * or, backend of the CVImage
 */
class CVImageImpl {
public:
	/**
	 * @brief load the image from file
	 * @param filename the file name to load
	 */
	virtual void load_from_file(const char* filename) = 0;

	/**
	 * @brief assigned the image to this image
	 * @param impl the image to assign
	 * @param req_copy if true, then copy the image
	 */
	virtual void assigned(const CVImageImpl* impl, bool req_copy) = 0;

	/**
	 * @brief pass_copy makes a passing assigned, for OpenCV like
	 * it just increase the ref count
	 * @param copied
	 */
	virtual void pass_copy(const CVImageImpl* copied) = 0;
	virtual ~CVImageImpl() = default;

	/**
	 * @brief image_valid check if the image is valid
	 * @return true if the image is valid
	 */
	virtual bool image_valid() = 0;
};

class CVImageImplFactory {
public:
	/**
	 * @brief target_impl fetch the IMPL according platform/backend framework
	 * @return the target impl
	 * @note this will be used to create the impl
	 * already assigned the correct son classes
	 */
	static CVImageImpl* target_impl();
};

#endif // CVIMAGEIMPL_H
