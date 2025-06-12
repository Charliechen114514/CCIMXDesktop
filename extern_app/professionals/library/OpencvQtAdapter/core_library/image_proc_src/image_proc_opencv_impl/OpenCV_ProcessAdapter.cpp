#include "OpenCV_ProcessAdapter.h"
#include "CVImagePrivateOpencvImp.h"
#include <opencv2/opencv.hpp>

void OpenCV_ProcessAdapter::grayImage(CVImageImpl* image_mat, int code) {
    CVImageOpencvImpl* impl = dynamic_cast<CVImageOpencvImpl*>(image_mat);
    cv::Mat result;
    cv::cvtColor(impl->raw_image, result, cv::COLOR_BGR2GRAY);
    impl->raw_image = result.clone();
}

void OpenCV_ProcessAdapter::processBlurType(CVImageImpl* image_mat, int kernel_size) {
    CVImageOpencvImpl* impl = dynamic_cast<CVImageOpencvImpl*>(image_mat);
    cv::Mat result;
    cv::blur(impl->raw_image, result, cv::Size(kernel_size, kernel_size));
    impl->raw_image = result.clone();
}

void OpenCV_ProcessAdapter::processGaussainBlurType(CVImageImpl* image_mat, int kernel_size, double sigma_x, double sigma_y) {
    CVImageOpencvImpl* impl = dynamic_cast<CVImageOpencvImpl*>(image_mat);
    cv::Mat result;
    cv::GaussianBlur(impl->raw_image, result, cv::Size(kernel_size, kernel_size), sigma_x, sigma_y);
    impl->raw_image = result.clone();
}

void OpenCV_ProcessAdapter::processMedianBlurType(CVImageImpl* image_mat, int kernel_size) {
    CVImageOpencvImpl* impl = dynamic_cast<CVImageOpencvImpl*>(image_mat);
    cv::Mat result;
    cv::medianBlur(impl->raw_image, result, kernel_size);
    impl->raw_image = result.clone();
}

void OpenCV_ProcessAdapter::processFilterBlurType(CVImageImpl* image_mat, int d, double sigma_color, double sigma_space) {
    CVImageOpencvImpl* impl = dynamic_cast<CVImageOpencvImpl*>(image_mat);
    cv::Mat result;
    cv::bilateralFilter(impl->raw_image, result, d, sigma_color, sigma_space);
    impl->raw_image = result.clone();
}

void OpenCV_ProcessAdapter::processCannyDetection(CVImageImpl* image_mat, int low, int high) {
    CVImageOpencvImpl* impl = dynamic_cast<CVImageOpencvImpl*>(image_mat);
    cv::Mat result;
    cv::Canny(impl->raw_image, result, low, high);
    impl->raw_image = result.clone();
}

void OpenCV_ProcessAdapter::processContoursDrawSession(CVImageImpl* drawmap, CVImageImpl* postProcessed, int contoursMethod) {
    CVImageOpencvImpl* post_handle = dynamic_cast<CVImageOpencvImpl*>(postProcessed);
    CVImageOpencvImpl* drawer = dynamic_cast<CVImageOpencvImpl*>(drawmap);
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;
    cv::findContours(post_handle->raw_image, contours, hierarchy, cv::RETR_TREE, contoursMethod);
    cv::Mat result = drawer->raw_image.clone();
    for (size_t i = 0; i < contours.size(); i++) {
        cv::Scalar color(rand() % 256, rand() % 256, rand() % 256);
        cv::drawContours(result, contours, static_cast<int>(i), color, 2, cv::LINE_8, hierarchy, 0);
    }
    drawer->raw_image = result;
}

void OpenCV_ProcessAdapter::generate_hist(CVImageImpl* drawmap, const CVImageImpl* src) {
    const CVImageOpencvImpl* src_handle = dynamic_cast<const CVImageOpencvImpl*>(src);
    CVImageOpencvImpl* drawer = dynamic_cast<CVImageOpencvImpl*>(drawmap);

    constexpr int histSize = 256;
    float range[] = { 0, histSize };
    const float* histRange = { range };
    cv::Mat hist;
    cv::Mat cloner = src_handle->raw_image.clone();
    cv::cvtColor(cloner, cloner, cv::COLOR_BGR2GRAY);
    cv::calcHist(&cloner, 1, 0, cv::Mat(), hist, 1, &histSize, &histRange);

    constexpr int histW = 512;
    constexpr int histH = 400;
    int binW = cvRound((double)histW / histSize);
    cv::Mat histImage(histH, histW, CV_8UC3, cv::Scalar(0, 0, 0));

    cv::normalize(hist, hist, 0, histImage.rows, cv::NORM_MINMAX);
    for (int i = 1; i < histSize; i++) {
        cv::line(histImage,
                 cv::Point(binW * (i - 1), histH - cvRound(hist.at<float>(i - 1))),
                 cv::Point(binW * i, histH - cvRound(hist.at<float>(i))),
                 cv::Scalar(255, 255, 255), 2);
    }
    drawer->raw_image = histImage.clone();
}

#include <QString>
#include <QTemporaryFile>
#include <stdexcept>
bool loadCascadeFromQrc(cv::CascadeClassifier& classifier, const QString& qrcPath) {
    Q_INIT_RESOURCE(sources);
    QFile file(qrcPath);

    if (!file.open(QIODevice::ReadOnly)) {
        return false;
    }

    QTemporaryFile tempFile;
    if (!tempFile.open()) {
        return false;
    }

    tempFile.write(file.readAll());
    tempFile.flush();

    return classifier.load(tempFile.fileName().toStdString());
}

void OpenCV_ProcessAdapter::draw_faces(CVImageImpl* drawmap, const CVImageImpl* src) {
    const CVImageOpencvImpl* src_handle = dynamic_cast<const CVImageOpencvImpl*>(src);
    CVImageOpencvImpl* drawer = dynamic_cast<CVImageOpencvImpl*>(drawmap);

    cv::CascadeClassifier face_cascade;
    if (!loadCascadeFromQrc(face_cascade, ":/models/haarcascade_frontalface_default.xml")) {
        throw std::runtime_error("Failed to load the model file");
    }

    cv::Mat gray;
    cv::Mat cloner = src_handle->raw_image.clone();
    cv::cvtColor(cloner, gray, cv::COLOR_BGR2GRAY);
    cv::equalizeHist(gray, gray);

    std::vector<cv::Rect> faces;
    face_cascade.detectMultiScale(gray, faces, 1.1, 4, 0, cv::Size(30, 30));

    for (size_t i = 0; i < faces.size(); ++i) {
        cv::rectangle(cloner, faces[i], cv::Scalar(0, 255, 0), 2);
    }

    drawer->raw_image = cloner;
}
