#ifndef COLORSELECTWIDGET_H
#define COLORSELECTWIDGET_H

#include <QWidget>

namespace Ui {
class ColorSelectWidget;
}

class ColorSelectWidget : public QWidget {
	Q_OBJECT

public:
    explicit ColorSelectWidget(QWidget* parent = nullptr);
	~ColorSelectWidget();
signals:
    void colorSelected(const QColor& color);

protected:
    void processSelectedColor(const QColor& color);

private:
    Ui::ColorSelectWidget* ui;
    QColor selectedColor;
};

#endif // COLORSELECTWIDGET_H
