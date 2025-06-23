#include "LabelStyler.h"
#include <QFont>
#include <QLabel>

template <typename WidgetType>
void LabelStyler<WidgetType>::setFontSize(int pointSize) {
    QFont f = label->font();
    f.setPointSize(pointSize);
    label->setFont(f);
}
template <typename WidgetType>
void LabelStyler<WidgetType>::setFont(const QFont& font) {
    label->setFont(font);
}
template <typename WidgetType>
void LabelStyler<WidgetType>::setTextColor(const QColor& color) {
    QPalette p = label->palette();
    p.setColor(QPalette::WindowText, color);
    label->setPalette(p);
}
