#ifndef LABEL_STYLER
#define LABEL_STYLER

/**
 * @file label_styler.h
 * @brief Declares the LabelStyler class for applying style changes to QLabel widgets.
 */

class QLabel;
class QColor;
class QFont;

/**
 * @class LabelStyler
 * @brief Provides utility methods to style a QLabel.
 *
 * This class allows modification of font size, font family, and text color of a QLabel instance.
 */
class LabelStyler {
public:
    /**
     * @brief Pointer to the QLabel to style.
     */
    QLabel* label = nullptr;

    /**
     * @brief Sets the font size of the label.
     * @param pointSize Font size in points.
     */
    void setFontSize(int pointSize);

    /**
     * @brief Sets the font of the label.
     * @param font The QFont to apply.
     */
    void setFont(const QFont& font);

    /**
     * @brief Sets the text color of the label.
     * @param color The QColor to apply.
     */
    void setTextColor(const QColor& color);

    /**
     * @brief Assigns the label to be styled.
     * @param lbl Pointer to the QLabel.
     */
    void setLabel(QLabel* lbl) {
        label = lbl;
    }
};

#endif // LABEL_STYLER
