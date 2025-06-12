#ifndef GRAYPROCESSOR_H
#define GRAYPROCESSOR_H
#include "image_proc_base.h"
/**
 * @brief make image gray
 * 
 */
class GrayProcessor : public ImageProc {
public:
	/**
	 * @brief Construct a new Gray Processor object
	 * 
	 */
	GrayProcessor();
    virtual ~GrayProcessor() override = default;
	/**
	 * @brief process the gray session
	 * 
	 * @param prev_image the image waiting handle
	 * @return result of processing
	 */
	bool process(CVImage& prev_image) override;
};

#endif // GRAYPROCESSOR_H
