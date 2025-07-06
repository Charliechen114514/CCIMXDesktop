#ifndef COLORPICKER_H
#define COLORPICKER_H

#include <QWidget>
class QPushButton;
class ColorPicker : public QWidget {
	Q_OBJECT
public:
    explicit ColorPicker(QWidget* parent = nullptr);
    QColor color() const;
    void setColor(const QColor& color);

signals:
    void colorChanged(const QColor& color);

private slots:
    void openColorDialog();

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    QPushButton* chooseButton;
    QColor currentColor;

    void updateStyle();
};

#endif // COLORPICKER_H
