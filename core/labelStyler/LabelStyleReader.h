#ifndef LABELSTYLEREADER_H
#define LABELSTYLEREADER_H

/**
 * @file labelstylereader.h
 * @brief Declares the LabelStyleReader class for retrieving QLabel style properties.
 */

#include <QLabel>
#include <QFont>
#include <QColor>

/**
 * @class LabelStyleReader
 * @brief Provides static methods to read style information from QLabel widgets.
 *
 * This includes reading font, font size, and text color from a QLabel.
 */
class LabelStyleReader {
public:
    /**
     * @brief Gets the font used in the label.
     * @param label Pointer to the QLabel.
     * @return The QFont applied to the label.
     */
    static QFont font(const QLabel* label);

    /**
     * @brief Gets the font size of the label in points.
     * @param label Pointer to the QLabel.
     * @return Font size in points.
     */
    static int fontSize(const QLabel* label);

    /**
     * @brief Gets the text color of the label.
     * @param label Pointer to the QLabel.
     * @return The QColor used for the label's text.
     */
    static QColor textColor(const QLabel* label);
};

#endif // LABELSTYLEREADER_H
