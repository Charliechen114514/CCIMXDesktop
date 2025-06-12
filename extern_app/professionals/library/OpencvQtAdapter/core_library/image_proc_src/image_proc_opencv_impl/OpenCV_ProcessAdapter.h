#ifndef OPENCV_PROCESSADAPTER_H
#define OPENCV_PROCESSADAPTER_H

/**
 * @brief Forward declaration of the CVImageImpl class used as an image container.
 */
class CVImageImpl;

/**
 * @brief Forward declaration of QString class from Qt framework.
 */
class QString;

/**
 * @brief The OpenCV_ProcessAdapter namespace provides wrapper functions to apply various OpenCV-based image processing operations.
 */
namespace OpenCV_ProcessAdapter {

    /**
     * @brief Converts the image to grayscale using the given conversion code.
     * @param image_mat Pointer to the image data.
     * @param code OpenCV color conversion code (e.g., cv::COLOR_BGR2GRAY).
     */
    void grayImage(CVImageImpl* image_mat, int code);

    /**
     * @brief Applies a simple blur to the image using the specified kernel size.
     * @param image_mat Pointer to the image data.
     * @param kernel_size The size of the kernel to be used for blurring.
     */
    void processBlurType(CVImageImpl* image_mat, int kernel_size);

    /**
     * @brief Applies a Gaussian blur to the image.
     * @param image_mat Pointer to the image data.
     * @param kernal_size The size of the kernel to be used for Gaussian blurring (must be odd).
     * @param sigma_x Gaussian kernel standard deviation in X direction.
     * @param sigma_y Gaussian kernel standard deviation in Y direction.
     */
    void processGaussainBlurType(CVImageImpl* image_mat,
                                 int kernal_size,
                                 double sigma_x, double sigma_y);

    /**
     * @brief Applies a median blur to the image using the specified kernel size.
     * @param image_mat Pointer to the image data.
     * @param kernel_size Size of the kernel; must be odd and greater than 1.
     */
    void processMedianBlurType(CVImageImpl* image_mat, int kernel_size);

    /**
     * @brief Applies a bilateral filter to the image.
     * @param image_mat Pointer to the image data.
     * @param d Diameter of each pixel neighborhood.
     * @param sigma_color Filter sigma in the color space.
     * @param sigma_space Filter sigma in the coordinate space.
     */
    void processFilterBlurType(CVImageImpl* image_mat, int d, double sigma_color, double sigma_space);

    /**
     * @brief Applies Canny edge detection to the image.
     * @param image_mat Pointer to the image data.
     * @param low Lower threshold for edge detection.
     * @param high Upper threshold for edge detection.
     */
    void processCannyDetection(CVImageImpl* image_mat, int low, int high);

    /**
     * @brief Draws contours found in the source image onto the destination map.
     * @param drawmap Destination image where contours will be drawn.
     * @param postProcessed Source image to detect contours from.
     * @param contoursMethod Integer specifying the OpenCV contour approximation method.
     */
    void processContoursDrawSession(CVImageImpl* drawmap, CVImageImpl* postProcessed, int contoursMethod);

    /**
     * @brief Generates a histogram visualization from the source image and draws it onto the drawmap.
     * @param drawmap The image to draw the histogram on.
     * @param src The source image from which the histogram is computed.
     */
    void generate_hist(CVImageImpl* drawmap, const CVImageImpl* src);

    /**
     * @brief Draws face detection results on the target image.
     * @param drawmap The image to draw results on.
     * @param src The source image used for face detection.
     */
    void draw_faces(CVImageImpl* drawmap, const CVImageImpl* src);

} // namespace OpenCV_ProcessAdapter

#endif // OPENCV_PROCESSADAPTER_H
