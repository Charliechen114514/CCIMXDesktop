#ifndef BLURPROCESSOR_H
#define BLURPROCESSOR_H

#include "image_proc_base.h"

/**
 * @brief The BlurProcessor class is an abstract image processor base for various blur operations.
 *
 * It defines the blur type and provides a base for concrete blur processors like mean, Gaussian, etc.
 */
class BlurProcessor : public ImageProc {
public:
    /**
     * @brief The HandleType enum lists supported blur types.
     */
    enum class HandleType {
        MedianBlur,    ///< Median filter blur
        GuassainBlur,  ///< Gaussian blur
        MeanBlur,      ///< Mean (average) blur
        FilterBlur     ///< Bilateral filter blur
    };

    /**
     * @brief Constructs a BlurProcessor with the specified blur type.
     * @param t The type of blur operation.
     */
    explicit BlurProcessor(const HandleType t)
        : type(t) { }

    /**
     * @brief Virtual destructor.
     */
    ~BlurProcessor() override = default;

    /**
     * @brief Returns the blur type of this processor.
     * @return The HandleType of the processor.
     */
    inline HandleType handleType() const { return type; }

private:
    HandleType type; ///< The type of blur operation.
};

/**
 * @brief The AbstractParamsPack struct serves as a base class for all blur parameter packs.
 *
 * This is a polymorphic base class used to pass blur parameters in a generic way.
 */
struct AbstractParamsPack {
    virtual ~AbstractParamsPack() = default;
};

/**
 * @brief Parameters for median blur processing.
 */
struct MedianBlurPackage : public AbstractParamsPack {
    ~MedianBlurPackage() override = default;

    /**
     * @brief Kernel size for the median blur.
     */
    int kernel_size { 5 };
};

/**
 * @brief Parameters for Gaussian blur processing.
 */
struct GaussainPackage : public AbstractParamsPack {
    /**
     * @brief Constructs a Gaussian package with default parameters.
     */
    GaussainPackage()
        : kernel_size(5)
        , sigma_x(1.5) {
        sigma_y = sigma_x;
    }

    ~GaussainPackage() override = default;

    /**
     * @brief Size of the kernel used for convolution.
     */
    int kernel_size;

    /**
     * @brief Standard deviation in the X direction.
     */
    double sigma_x;

    /**
     * @brief Standard deviation in the Y direction.
     */
    double sigma_y;
};

/**
 * @brief Parameters for bilateral filter blur.
 */
struct FilterPackage : public AbstractParamsPack {
    ~FilterPackage() override = default;

    /**
     * @brief Diameter of each pixel neighborhood.
     */
    int d;

    /**
     * @brief Filter sigma in the color space.
     */
    double sigma_space;

    /**
     * @brief Filter sigma in the coordinate space.
     */
    double sigma_color;
};

/**
 * @brief Parameters for mean blur processing.
 */
struct MeanBlurPackage : public AbstractParamsPack {
    ~MeanBlurPackage() override = default;

    /**
     * @brief Kernel size used in mean filtering.
     */
    int kernel_size { 5 };
};

/**
 * @brief Performs mean (average) blur on images.
 */
class MeanBlur : public BlurProcessor {
public:
    /**
     * @brief Constructs a MeanBlur processor.
     */
    MeanBlur();

    /**
     * @brief Destructor.
     */
    ~MeanBlur() override = default;

    /**
     * @brief Processes an image with internal parameters.
     * @param prev_image The input/output image.
     * @return true if processing is successful.
     */
    bool process(CVImage& prev_image) override;

    /**
     * @brief Static method to process image with given parameters.
     * @param prev_image The image to process.
     * @param package The parameter package.
     * @return true if processing is successful.
     */
    static bool process(CVImage& prev_image, const MeanBlurPackage& package);

    MeanBlurPackage package; ///< Parameters used in mean blur.
};

/**
 * @brief Performs Gaussian blur on images.
 */
class GuassainBlur : public BlurProcessor {
public:
    /**
     * @brief Constructs a GuassainBlur processor.
     */
    GuassainBlur();

    /**
     * @brief Destructor.
     */
    ~GuassainBlur() override = default;

    /**
     * @brief Processes an image with internal parameters.
     * @param prev_image The image to process.
     * @return true if processing succeeds.
     */
    bool process(CVImage& prev_image) override;

    /**
     * @brief Static method to process image with given Gaussian parameters.
     * @param prev_image The image to process.
     * @param package The Gaussian blur parameters.
     * @return true if successful.
     */
    static bool process(CVImage& prev_image, const GaussainPackage& package);

    GaussainPackage package; ///< Parameters used in Gaussian blur.
};

/**
 * @brief Performs median blur on images.
 */
class MedianBlur : public BlurProcessor {
public:
    /**
     * @brief Constructs a MedianBlur processor.
     */
    MedianBlur();

    /**
     * @brief Destructor.
     */
    ~MedianBlur() override = default;

    /**
     * @brief Processes an image with internal parameters.
     * @param prev_image The image to process.
     * @return true if processing is successful.
     */
    bool process(CVImage& prev_image) override;

    /**
     * @brief Static method to apply median blur with external parameters.
     * @param prev_image The image to process.
     * @param package The median blur parameters.
     * @return true if successful.
     */
    static bool process(CVImage& prev_image, const MedianBlurPackage& package);

    MedianBlurPackage package; ///< Parameters used in median blur.
};

/**
 * @brief Performs bilateral filter blur on images.
 */
class FilterBlur : public BlurProcessor {
public:
    /**
     * @brief Constructs a FilterBlur processor.
     */
    FilterBlur();

    /**
     * @brief Destructor.
     */
    ~FilterBlur() override = default;

    /**
     * @brief Processes an image with internal parameters.
     * @param prev_image The image to process.
     * @return true if processing is successful.
     */
    bool process(CVImage& prev_image) override;

    /**
     * @brief Static method to apply bilateral filter blur.
     * @param prev_image The image to process.
     * @param package The filter parameters.
     * @return true if successful.
     */
    static bool process(CVImage& prev_image, const FilterPackage& package);

    FilterPackage package; ///< Parameters used in bilateral filter blur.
};

#endif // BLURPROCESSOR_H
