#include "TimeDisplayIconWidget.h"
#include "../DefaultLabelName.h"
#include "ui_TimeDisplayIconWidget.h"
TimeDisplayIconWidget::TimeDisplayIconWidget(QWidget* parent)
    : StatusBarIconWidget(TopStatusBar_LabelName::TIME, parent)
    , ui(new Ui::TimeDisplayIconWidget) {
	ui->setupUi(this);
}

TimeDisplayIconWidget::~TimeDisplayIconWidget() {
	delete ui;
}

QLabel* TimeDisplayIconWidget::displayedLabel() const {
    return ui->label;
}

void TimeDisplayIconWidget::update_displayTime(QTime time) {
    ui->label->setText(time.toString("hh:mm"));
}
