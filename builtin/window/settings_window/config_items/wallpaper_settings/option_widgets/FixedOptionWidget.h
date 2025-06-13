#ifndef FIXEDOPTIONWIDGET_H
#define FIXEDOPTIONWIDGET_H

#include <QWidget>

namespace Ui {
class FixedOptionWidget;
}

/**
 * @brief The FixedOptionWidget class
 * A widget that displays a fixed image option and reacts to user interaction.
 * 
 * This widget provides a visual option using a pixmap. It may be used as a selectable item
 * within a larger interface, such as a wallpaper or icon chooser.
 */
class FixedOptionWidget : public QWidget {
    Q_OBJECT

public:
    /**
     * @brief Constructs the FixedOptionWidget.
     * @param parent Optional parent QWidget.
     */
    explicit FixedOptionWidget(QWidget* parent = nullptr);

    /**
     * @brief Sets the pixmap to be displayed.
     * @param pixmap The image to display.
     */
    void setPixmap(const QPixmap& pixmap);

    /**
     * @brief Retrieves the current displayed pixmap.
     * @return The currently set pixmap.
     */
    QPixmap get_pixmap() const;

    /**
     * @brief Destructor.
     */
    ~FixedOptionWidget();

private slots:
    /**
     * @brief Handles new selections (e.g., user clicked this option).
     */
    void handle_new_selections();

private:
    Ui::FixedOptionWidget* ui; ///< UI pointer.
};

#endif // FIXEDOPTIONWIDGET_H
