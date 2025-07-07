#ifndef COLORPICKER_H
#define COLORPICKER_H

#include <QWidget>

class QPushButton;

/**
 * @class ColorPicker
 * @brief A widget for selecting and displaying colors
 *
 * Provides a button that opens a color dialog when clicked and displays
 * the currently selected color.
 */
class ColorPicker : public QWidget {
    Q_OBJECT
public:
    /**
     * @brief Constructs a ColorPicker widget
     * @param parent The parent widget
     */
    explicit ColorPicker(QWidget* parent = nullptr);

    /**
     * @brief Gets the currently selected color
     * @return The current QColor
     */
    QColor color() const;

    /**
     * @brief Sets the current color
     * @param color The color to set
     */
    void setColor(const QColor& color);

signals:
    /**
     * @brief Emitted when the color changes
     * @param color The new color
     */
    void colorChanged(const QColor& color);

private slots:
    /**
     * @brief Opens the color selection dialog
     */
    void openColorDialog();

protected:
    /**
     * @brief Handles paint events
     * @param event The paint event
     */
    void paintEvent(QPaintEvent* event) override;

private:
    QPushButton* chooseButton; /**< Button to trigger color selection */
    QColor currentColor; /**< Currently selected color */

    /**
     * @brief Updates the widget's style
     */
    void updateStyle();
};

#endif // COLORPICKER_H
