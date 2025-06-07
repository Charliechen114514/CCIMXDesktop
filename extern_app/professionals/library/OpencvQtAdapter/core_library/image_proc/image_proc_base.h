#ifndef IMAGE_PROC_BASE_H
#define IMAGE_PROC_BASE_H
class CVImage;
struct ImageProc {
	ImageProc() = default;
	virtual ~ImageProc() = default;
	virtual bool process(CVImage& prev_image) = 0;
};

#endif // IMAGE_PROC_BASE_H
