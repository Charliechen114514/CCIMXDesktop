#include "ColorSelectWidget.h"
#include "ui_ColorSelectWidget.h"
#include <QColorDialog>
ColorSelectWidget::ColorSelectWidget(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::ColorSelectWidget) {
	ui->setupUi(this);
    connect(ui->btn_select, &QPushButton::clicked,
            this, [this]() {
                QColor color = QColorDialog::getColor(Qt::white, this);
                if (!color.isValid()) {
                    return;
                }
                emit colorSelected(color);
            });
    connect(this, &ColorSelectWidget::colorSelected,
            this, &ColorSelectWidget::processSelectedColor);
}

ColorSelectWidget::~ColorSelectWidget() {
	delete ui;
}

void ColorSelectWidget::processSelectedColor(const QColor& color) {
    this->selectedColor = color;
    ui->colorLabel->setStyleSheet(QString("background-color: rgb(%1, %2, %3);")
                                      .arg(color.red())
                                      .arg(color.green())
                                      .arg(color.blue()));
}
