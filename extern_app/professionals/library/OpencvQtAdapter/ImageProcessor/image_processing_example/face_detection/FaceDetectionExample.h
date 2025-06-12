#ifndef FACEDETECTIONEXAMPLE_H
#define FACEDETECTIONEXAMPLE_H

#include <QWidget>

namespace Ui {
class FaceDetectionExample;
}

/**
 * @brief The FaceDetectionExample class
 * Widget for demonstrating face detection on an image.
 */
class FaceDetectionExample : public QWidget {
    Q_OBJECT

public:
    /**
     * @brief Construct a new FaceDetectionExample widget
     * @param parent The parent widget, or nullptr if none
     */
    explicit FaceDetectionExample(QWidget* parent = nullptr);

    /**
     * @brief Destroy the FaceDetectionExample widget
     */
    ~FaceDetectionExample();

private:
    /**
     * @brief Process the image and perform face detection
     */
    void process_image_session();

    /**
     * @brief Pointer to the UI elements generated from the .ui file
     */
    Ui::FaceDetectionExample* ui;
};

#endif // FACEDETECTIONEXAMPLE_H
