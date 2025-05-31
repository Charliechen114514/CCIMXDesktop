#ifndef CAMERADISPLAYWIDGET_H
#define CAMERADISPLAYWIDGET_H

#include <QWidget>
#include <QImage>
#include <QPixmap>

namespace Ui {
class CameraDisplayWidget;
}

/**
 * @brief The CameraDisplayWidget class
 * A QWidget-derived class that displays camera frames.
 * It allows setting the current frame as a QImage and
 * retrieving the currently displayed frame as a QPixmap.
 */
class CameraDisplayWidget : public QWidget {
    Q_OBJECT

public:
    /**
     * @brief Constructor with optional parent widget.
     * @param parent The parent QWidget, default is nullptr.
     */
    explicit CameraDisplayWidget(QWidget* parent = nullptr);

    /**
     * @brief Destructor.
     * Cleans up the UI resources.
     */
    ~CameraDisplayWidget();

    /**
     * @brief setCurrentFrame
     * Sets the current frame image to be displayed.
     * @param image The QImage frame to display.
     */
    void setCurrentFrame(const QImage& image);

    /**
     * @brief current_captures
     * Retrieves the currently displayed frame as a QPixmap.
     * @return The current frame as QPixmap.
     */
    QPixmap current_captures() const;

private:
    Ui::CameraDisplayWidget* ui; ///< Pointer to the UI elements.
};

#endif // CAMERADISPLAYWIDGET_H
