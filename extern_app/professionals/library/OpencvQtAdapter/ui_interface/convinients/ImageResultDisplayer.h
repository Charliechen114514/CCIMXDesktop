#ifndef IMAGERESULTDISPLAYER_H
#define IMAGERESULTDISPLAYER_H

#include <QWidget>

class ImageLabel;
class QLabel;

namespace Ui {
/**
 * @brief Forward declaration of the auto-generated UI class.
 */
class ImageResultDisplayer;
}

/**
 * @brief The ImageResultDisplayer class provides a QWidget-based UI component
 * for displaying a pair of images: the original (raw) and the processed result.
 *
 * This widget is typically used in image processing applications to present
 * a visual comparison between input and output stages.
 */
class ImageResultDisplayer : public QWidget {
    Q_OBJECT

public:
    /**
     * @brief Constructs an ImageResultDisplayer with an optional parent.
     * @param parent The parent widget.
     */
    explicit ImageResultDisplayer(QWidget* parent = nullptr);

    /**
     * @brief Destructor for ImageResultDisplayer.
     */
    ~ImageResultDisplayer();

    /**
     * @brief Returns the label widget displaying the raw/original image.
     * @return Pointer to the raw ImageLabel.
     */
    ImageLabel* rawImageLabel();

    /**
     * @brief Returns the label widget displaying the processed image.
     * @return Pointer to the processed ImageLabel.
     */
    ImageLabel* processedImageLabel();

public slots:
    /**
     * @brief Sets the raw image to be displayed.
     * @param image The QImage representing the original input image.
     */
    void setRawImage(const QImage& image);

    /**
     * @brief Sets the processed image to be displayed.
     * @param image The QImage representing the result of image processing.
     */
    void setProcessedImage(const QImage& image);

private:
    /**
     * @brief Pointer to the auto-generated UI layout.
     */
    Ui::ImageResultDisplayer* ui;
};

#endif // IMAGERESULTDISPLAYER_H
