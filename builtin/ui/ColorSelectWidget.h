#ifndef COLORSELECTWIDGET_H
#define COLORSELECTWIDGET_H

/**
 * @file colorselectwidget.h
 * @brief Declares the ColorSelectWidget class for selecting a color in a UI component.
 */

#include <QWidget>
#include <QColor>

namespace Ui {
/**
 * @brief Forward declaration of the UI class generated by Qt Designer.
 */
class ColorSelectWidget;
}

/**
 * @class ColorSelectWidget
 * @brief A widget that allows users to select a color.
 *
 * This widget provides a UI for selecting a color and emits a signal when a color is chosen.
 */
class ColorSelectWidget : public QWidget {
    Q_OBJECT

public:
    /**
     * @brief Constructs a ColorSelectWidget.
     * @param parent Optional parent widget.
     */
    explicit ColorSelectWidget(QWidget* parent = nullptr);

    /**
     * @brief Destructor.
     */
    ~ColorSelectWidget();

signals:
    /**
     * @brief Emitted when the user selects a color.
     * @param color The selected QColor.
     */
    void colorSelected(const QColor& color);

protected:
    /**
     * @brief Processes the selected color internally.
     * @param color The QColor to process.
     */
    void processSelectedColor(const QColor& color);

private:
    /**
     * @brief Pointer to the UI elements managed by Qt Designer.
     */
    Ui::ColorSelectWidget* ui;

    /**
     * @brief The currently selected color.
     */
    QColor selectedColor;
};

#endif // COLORSELECTWIDGET_H
