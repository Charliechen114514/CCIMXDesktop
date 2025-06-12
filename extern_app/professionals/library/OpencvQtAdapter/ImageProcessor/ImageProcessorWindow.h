#ifndef IMAGEPROCESSORWINDOW_H
#define IMAGEPROCESSORWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class ImageProcessorWindow;
}
QT_END_NAMESPACE

/**
 * @brief The ImageProcessorWindow class
 * Main window for the image processing application.
 */
class ImageProcessorWindow : public QMainWindow {
    Q_OBJECT

public:
    /**
     * @brief Construct a new ImageProcessorWindow object
     * @param parent The parent widget, or nullptr if none
     */
    ImageProcessorWindow(QWidget* parent = nullptr);

    /**
     * @brief Destroy the ImageProcessorWindow object
     */
    ~ImageProcessorWindow();

private:
    /**
     * @brief Pointer to the UI elements generated from the .ui file
     */
    Ui::ImageProcessorWindow* ui;

    /**
     * @brief Setup the control panel and initialize UI logic
     */
    void setup_panel();
};

#endif // IMAGEPROCESSORWINDOW_H
