#include "LabelStyler.h"
#include <QFont>
#include <QLabel>

void LabelStyler::setFontSize(int pointSize) {
    QFont f = label->font();
    f.setPointSize(pointSize);
    label->setFont(f);
}

void LabelStyler::setFont(const QFont& font) {
    label->setFont(font);
}

void LabelStyler::setTextColor(const QColor& color) {
    QPalette p = label->palette();
    p.setColor(QPalette::WindowText, color);
    label->setPalette(p);
}
