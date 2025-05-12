#include "ScrollingLabel.h"
#include "ui_ScrollingLabel.h"
#include <QTimer>
ScrollingLabel::ScrollingLabel(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::ScrollingLabel) {
	ui->setupUi(this);
	connect(&timer, &QTimer::timeout, this, &ScrollingLabel::scrollText);
	timer.setInterval(ANIMATION_INTERVAL);
	ui->label->move(0, 0);
}

void ScrollingLabel::setText(const QString& text) {
	ui->label->setText(text);
	ui->label->adjustSize();
	offset = 0;
	updateScroll();
}

ScrollingLabel::~ScrollingLabel() {
	delete ui;
}

void ScrollingLabel::scrollText() {
	offset -= STEP_SHORT;
	int textWidth = ui->label->width();
	int widgetWidth = width();

	if (textWidth <= widgetWidth) {
		ui->label->move(0, 0); // 不滚动
		timer.stop();
		return;
	}

	if (offset + textWidth < 0) {
		offset = widgetWidth;
	}

	ui->label->move(offset, 0);
}

void ScrollingLabel::updateScroll() {
	int textWidth = ui->label->width();
	int widgetWidth = width();
	offset = 0;
	ui->label->move(0, 0);
	textWidth <= widgetWidth ? timer.stop() : timer.start();
}
