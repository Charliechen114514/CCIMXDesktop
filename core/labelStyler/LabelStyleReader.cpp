#include "LabelStyleReader.h"

QFont LabelStyleReader::font(const QLabel* label) {
    if (label) {
        return label->font();
    }
    return QFont();
}

int LabelStyleReader::fontSize(const QLabel* label) {
    if (label) {
        return label->font().pointSize();
    }
    return -1;
}

QColor LabelStyleReader::textColor(const QLabel* label) {
    if (label) {
        return label->palette().color(QPalette::WindowText);
    }
    return QColor();
}
