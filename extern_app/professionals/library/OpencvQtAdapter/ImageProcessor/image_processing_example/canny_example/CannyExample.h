#ifndef CANNYEXAMPLE_H
#define CANNYEXAMPLE_H

#include <QWidget>

namespace Ui {
class CannyExample;
}

/**
 * @brief The CannyExample class
 * This widget demonstrates the application of the Canny edge detection algorithm.
 */
class CannyExample : public QWidget {
    Q_OBJECT

public:
    /**
     * @brief Construct a new CannyExample widget
     * @param parent The parent widget, or nullptr if none
     */
    explicit CannyExample(QWidget* parent = nullptr);

    /**
     * @brief Destroy the CannyExample widget
     */
    ~CannyExample();

    /**
     * @brief Processes the image using Canny edge detection
     */
    void process_image_session();

private:
    /**
     * @brief Pointer to the UI elements generated from the .ui file
     */
    Ui::CannyExample* ui;
};

#endif // CANNYEXAMPLE_H
