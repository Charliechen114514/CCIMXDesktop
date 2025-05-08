#ifndef CVIMAGEIMPL_H
#define CVIMAGEIMPL_H
/* class interfaces */

class CVImageImpl {
public:
	virtual void load_from_file(const char* filename) = 0;
	virtual void assigned(const CVImageImpl* impl, bool req_copy) = 0;
	virtual void pass_copy(const CVImageImpl* copied) = 0;
	virtual ~CVImageImpl() = default;
	virtual bool image_valid() = 0;
};

class CVImageImplFactory {
public:
	/*
	 * create from here, already assigned the
	 * correct son classes
	 */
	static CVImageImpl* target_impl();
};

#endif // CVIMAGEIMPL_H
