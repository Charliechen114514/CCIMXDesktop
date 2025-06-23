#ifndef LABEL_STYLER
#define LABEL_STYLER
class QLabel;
class QColor;
class QFont;

class LabelStyler {
public:
    QLabel* label = nullptr;
    void setFontSize(int pointSize);
    void setFont(const QFont& font);
    void setTextColor(const QColor& color);
    void setLabel(QLabel* lbl) {
        label = lbl;
    }
};

#endif
