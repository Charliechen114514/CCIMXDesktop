#include "ColorPicker.h"
#include <QColorDialog>
#include <QHBoxLayout>
#include <QPainter>
#include <QPushButton>
#include <QStyleOption>
ColorPicker::ColorPicker(QWidget* parent)
    : QWidget { parent } {
    chooseButton = new QPushButton("Select Color", this);
    chooseButton->setFixedHeight(30);

    auto* layout = new QHBoxLayout(this);
    layout->addSpacing(8);
    layout->addWidget(chooseButton);
    layout->addStretch();
    layout->setContentsMargins(50, 5, 10, 5);
    setLayout(layout);

    connect(chooseButton, &QPushButton::clicked, this, &ColorPicker::openColorDialog);
    updateStyle();
}

QColor ColorPicker::color() const {
    return currentColor;
}

void ColorPicker::setColor(const QColor& color) {
    if (color != currentColor) {
        currentColor = color;
        update();
        emit colorChanged(currentColor);
    }
}

void ColorPicker::openColorDialog() {
    QColorDialog dialog(currentColor, this);
    dialog.setOption(QColorDialog::ShowAlphaChannel);
    if (dialog.exec() == QDialog::Accepted) {
        setColor(dialog.selectedColor());
    }
}

void ColorPicker::paintEvent(QPaintEvent* event) {
    QWidget::paintEvent(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    const int radius = 20;
    QRect circleRect(10, height() / 2 - radius / 2, radius, radius);

    painter.setBrush(currentColor);
    painter.setPen(Qt::NoPen);
    painter.drawEllipse(circleRect);
}

void ColorPicker::updateStyle() {
    chooseButton->setStyleSheet(R"(
        QPushButton {
            background-color: #e0f0ff;
            color: #003366;
            border: 1px solid #a0c8e0;
            border-radius: 6px;
            padding: 4px 12px;
            font-weight: bold;
        }
        QPushButton:hover {
            background-color: #cce7ff;
        }
        QPushButton:pressed {
            background-color: #b3dcff;
        }
    )");
    this->setStyleSheet(R"(
        ColorPickerWidget {
            background-color: #f5fbff;
        }
    )");
}
