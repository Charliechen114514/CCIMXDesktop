#ifndef GRAYPROCESSOR_H
#define GRAYPROCESSOR_H
#include "image_proc_base.h"
class GrayProcessor : public ImageProc {
public:
	GrayProcessor();
    virtual ~GrayProcessor() override = default;
	bool process(CVImage& prev_image) override;
};

#endif // GRAYPROCESSOR_H
