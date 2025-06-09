#ifndef BLURPROCESSOR_H
#define BLURPROCESSOR_H

#include "image_proc_base.h"

class BlurProcessor : public ImageProc {
public:
    enum class HandleType {
        MedianBlur,
        GuassainBlur,
        MeanBlur,
        FilterBlur,
    };
    BlurProcessor(const HandleType t)
        : type(t) { };
    virtual ~BlurProcessor() override = default;
    inline HandleType handleType() const { return type; }

private:
    HandleType type;
};

/**
 * @brief The AbstractParamsPack class
 * really matters in using interface like params
 */
struct AbstractParamsPack {
    virtual ~AbstractParamsPack() = default;
};

struct MedianBlurPackage : public AbstractParamsPack {
    ~MedianBlurPackage() override = default;
    int kernel_size { 5 };
};

struct GaussainPackage : AbstractParamsPack {
    GaussainPackage()
        : kernel_size(5)
        , sigma_x(1.5) {
        sigma_y = sigma_x;
    }
    ~GaussainPackage() = default;
    int kernel_size;
    double sigma_x;
    double sigma_y;
};

struct FilterPackage : AbstractParamsPack {
    ~FilterPackage() = default;
    int d;
    double sigma_space;
    double sigma_color;
};

struct MeanBlurPackage : public AbstractParamsPack {
    ~MeanBlurPackage() override = default;
    int kernel_size { 5 };
};

class MeanBlur : BlurProcessor {
public:
    MeanBlur();
    ~MeanBlur() override = default;
    bool process(CVImage& prev_image) override;
    static bool process(CVImage& prev_image, const MeanBlurPackage& package);
    MeanBlurPackage package;
};

class GuassainBlur : BlurProcessor {
public:
    GuassainBlur();
    ~GuassainBlur() override = default;
    bool process(CVImage& prev_image) override;
    static bool process(CVImage& prev_image, const GaussainPackage& package);
    GaussainPackage package;
};

class MedianBlur : BlurProcessor {
public:
    MedianBlur();
    ~MedianBlur() override = default;
    bool process(CVImage& prev_image) override;
    static bool process(CVImage& prev_image, const MedianBlurPackage& package);
    MedianBlurPackage package;
};

class FilterBlur : BlurProcessor {
public:
    FilterBlur();
    ~FilterBlur() override = default;
    bool process(CVImage& prev_image) override;
    static bool process(CVImage& prev_image, const FilterPackage& package);
    FilterPackage package;
};

#endif // BLURPROCESSOR_H
