#include "digitaltimewidget.h"
#include <QPainter>
DigitalTimeWidget::DigitalTimeWidget(QWidget* parent)
    : QWidget { parent } {
    stored_time = QTime::currentTime();
}

void DigitalTimeWidget::process_time_update(QTime process_time) {
    stored_time = process_time;
    update();
}

void DigitalTimeWidget::paintEvent(QPaintEvent* event) {
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);

    QTime time = stored_time;
	QString timeText = time.toString("hh:mm:ss");

	QDate date = QDate::currentDate();
	QString dateText = date.toString("yyyy MMM dd ddd");

	QFont timeFont("Helvetica Neue", 40, QFont::Bold);
	painter.setFont(timeFont);
	QFontMetrics timeMetrics(timeFont);
	int timeTextHeight = timeMetrics.height();

	QRect widgetRect = rect();
	QRect timeRect = widgetRect;
	timeRect.setHeight(timeTextHeight);
	timeRect.moveTop(widgetRect.center().y() - timeTextHeight); // 垂直居中

	painter.setPen(Qt::white);
	painter.drawText(timeRect, Qt::AlignCenter, timeText);

	QFont dateFont("Helvetica Neue", 15, QFont::Light);
	painter.setFont(dateFont);
	QFontMetrics dateMetrics(dateFont);
	int dateTextHeight = dateMetrics.height();

	QRect dateRect = widgetRect;
	dateRect.setHeight(dateTextHeight);
	dateRect.moveTop(timeRect.bottom() + 10);

	painter.drawText(dateRect, Qt::AlignCenter, dateText);
}
