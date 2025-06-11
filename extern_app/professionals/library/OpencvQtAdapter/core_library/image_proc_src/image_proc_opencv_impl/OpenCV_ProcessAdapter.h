#ifndef OPENCV_PROCESSADAPTER_H
#define OPENCV_PROCESSADAPTER_H
class CVImageImpl;

namespace OpenCV_ProcessAdapter {
void grayImage(CVImageImpl* image_mat, int code);

void processBlurType(CVImageImpl* image_mat, int kernel_size);

void processGaussainBlurType(CVImageImpl* image_mat,
                             int kernal_size,
                             double sigma_x, double sigma_y);

void processMedianBlurType(CVImageImpl* image_mat, int kernel_size);

void processFilterBlurType(CVImageImpl* image_mat, int d, double sigma_color, double sigma_space);

void processCannyDetection(CVImageImpl* image_mat, int low, int high);

void processContoursDrawSession(CVImageImpl* drawmap, CVImageImpl* postProcessed, int contoursMethod);
};

#endif // OPENCV_PROCESSADAPTER_H
