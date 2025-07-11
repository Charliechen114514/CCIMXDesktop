#ifndef CANNYPROCESSOR_H
#define CANNYPROCESSOR_H
#include "BlurProcessor.h"
#include "GrayProcessor.h"
#include "image_proc_base.h"
#include <utility>
/**
 * @namespace Processor::Canny
 * @brief settings
 * 
 */
namespace Processor {
namespace Canny {
    static constexpr unsigned int LOW = 50; ///< LOW Thredholds
    static constexpr unsigned int HIGH = 150; ///< HIGH Thredholds

    static constexpr unsigned int def_blurksize = 5; ///< ksize
    static constexpr float thred = 1.4; ///< floaty thred
}
}
/**
 * @brief CannyProcessor process Canny lol
 * 
 */
class CannyProcessor : public ImageProc {
public:
    CannyProcessor()
        : ImageProc() {
        blur.package.sigma_x = Processor::Canny::thred;
        blur.package.sigma_y = Processor::Canny::thred;
        blur.package.kernel_size = Processor::Canny::def_blurksize;
    }
    ~CannyProcessor() override = default;
    bool process(CVImage& prev_image) override;
    /**
     * @brief setParamsPackage
     * if you want to modified the gaussain package
     * interfaces is ready for settings!
     */
    inline void setParamsPackage(const GaussainPackage& package) {
        blur.package = package;
    }
    std::pair<int, int> threholds_pair = {
        Processor::Canny::LOW,
        Processor::Canny::HIGH
    }; ///< pair controller

private:
    GrayProcessor gray; ///< gray processor
    GuassainBlur blur; ///< blur processor
};

#endif // CANNYPROCESSOR_H
