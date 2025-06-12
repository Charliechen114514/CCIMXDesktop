#ifndef HISTDRAWER_H
#define HISTDRAWER_H

#include <QWidget>

namespace Ui {
class HistDrawer;
}

/**
 * @brief The HistDrawer class
 * Widget for generating and displaying histograms of image data.
 */
class HistDrawer : public QWidget {
    Q_OBJECT

public:
    /**
     * @brief Construct a new HistDrawer widget
     * @param parent The parent widget, or nullptr if none
     */
    explicit HistDrawer(QWidget* parent = nullptr);

    /**
     * @brief Destroy the HistDrawer widget
     */
    ~HistDrawer();

private:
    /**
     * @brief Process the image and generate histogram visualization
     */
    void process_image_session();

    /**
     * @brief Pointer to the UI elements generated from the .ui file
     */
    Ui::HistDrawer* ui;
};

#endif // HISTDRAWER_H
