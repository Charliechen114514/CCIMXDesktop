#include "clockwidget.h"
#include "ui_clockwidget.h"
#include <QPainter>
#include <QTime>
#include <QTimer>

ClockWidget::ClockWidget(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::ClockWidget) {
    ui->setupUi(this);
    internal_updater = new QTimer(this);

	connect(internal_updater, &QTimer::timeout,
			this, &ClockWidget::process_update_invokation);
	this->cur_time = QTime::currentTime();
	internal_updater->setInterval(1000);
	internal_updater->start();
}

ClockWidget::~ClockWidget() {
	delete ui;
}

void ClockWidget::paintEvent(QPaintEvent* _paintEvent) {
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);

	int side = qMin(width(), height());
	painter.translate(width() / 2, height() / 2);
	painter.scale(side / static_cast<double>(DialSize), side / static_cast<double>(DialSize));

	drawBackground(&painter);
	drawNumbers(&painter);
	drawTicks(&painter);
	drawHands(&painter);
	drawCenterDot(&painter);
}

QSize ClockWidget::sizeHint() const {
	return QSize(DefaultWidgetSize, DefaultWidgetSize);
}

void ClockWidget::process_update_invokation() {
	/* shell also process other things */
	emit time_update(cur_time);
	/* invoke this to pushing the draw sessions into the message queues */
	update();
}

void ClockWidget::drawBackground(QPainter* painter) {
	painter->save();
	painter->setPen(Qt::NoPen);

	constexpr int ThickBorderWidth = 8;
	painter->setPen(QPen(QColor(0, 0, 0), ThickBorderWidth));
	painter->setBrush(Qt::NoBrush);
	painter->drawEllipse(
		QPoint(0, 0), OuterCircleRadius - ThickBorderWidth / 2,
		OuterCircleRadius - ThickBorderWidth / 2);

	QRadialGradient gradient(0, 0, OuterCircleRadius);
	gradient.setColorAt(0.0, QColor(255, 255, 255));
	gradient.setColorAt(1.0, QColor(230, 230, 230));
	painter->setBrush(gradient);
	painter->drawEllipse(QPoint(0, 0), OuterCircleRadius, OuterCircleRadius);

	painter->setPen(QPen(QColor(200, 200, 200), 2));
	painter->setBrush(Qt::NoBrush);
	painter->drawEllipse(QPoint(0, 0), OuterCircleRadius, OuterCircleRadius);
	painter->restore();
}

void ClockWidget::drawNumbers(QPainter* painter) {
	painter->save();
	QFont font = painter->font();
	font.setPointSize(NumberFontSize);
	painter->setFont(font);
	painter->setPen(Qt::black);

	// Coordinates for 12, 3, 6, 9
	struct NumberInfo {
		int number;
		double angleDegree;
	};

	static constexpr NumberInfo numbers[] = {
		{ 12, 0 },
		{ 3, 90 },
		{ 6, 180 },
		{ 9, 270 }
	};

	for (const auto& num : numbers) {
		double radians = qDegreesToRadians(num.angleDegree);
		double x = NumberDistanceFromCenter * qSin(radians);
		double y = -NumberDistanceFromCenter * qCos(radians);

		QString text = QString::number(num.number);
		QRectF rect(x - 10, y - 10, 20, 20);
		painter->drawText(rect, Qt::AlignCenter, text);
	}

	painter->restore();
}

void ClockWidget::drawTicks(QPainter* painter) {
	painter->save();
	painter->setPen(QPen(Qt::black, HourTickWidth));
	for (int i = 0; i < 12; ++i) {
		painter->drawLine(0, -(OuterCircleRadius - HourTickLength), 0, -OuterCircleRadius);
		painter->rotate(HourRotationPerHour);
	}
	painter->setPen(QPen(Qt::gray, MinuteTickWidth));
	for (int i = 0; i < 60; ++i) {
		if (i % 5 != 0) {
			painter->drawLine(0, -(OuterCircleRadius - MinuteTickLength), 0, -OuterCircleRadius);
		}
		painter->rotate(MinuteRotationPerMinute);
	}
	painter->restore();
}

void ClockWidget::drawHands(QPainter* painter) {
	this->cur_time = QTime::currentTime();

	// Draw hour hand
	painter->save();
	painter->setPen(Qt::NoPen);
	painter->setBrush(Qt::black);
	painter->rotate(HourRotationPerHour * (cur_time.hour() % 12) + cur_time.minute() / 2.0);
	static const QPoint hourHand[4] = {
		QPoint(0, HandWidth),
		QPoint(-4, 0),
		QPoint(0, -HourHandLength),
		QPoint(4, 0)
	};
	painter->drawConvexPolygon(hourHand, 4);
	painter->restore();

	// Draw minute hand
	painter->save();
	painter->setPen(Qt::NoPen);
	painter->setBrush(Qt::black);
	painter->rotate(MinuteRotationPerMinute * cur_time.minute() + cur_time.second() / 10.0);
	static const QPoint minuteHand[4] = {
		QPoint(0, HandWidth),
		QPoint(-3, 0),
		QPoint(0, -MinuteHandLength),
		QPoint(3, 0)
	};
	painter->drawConvexPolygon(minuteHand, 4);
	painter->restore();

	// Draw second hand
	painter->save();
	painter->setPen(Qt::NoPen);
	painter->setBrush(Qt::red);
	painter->rotate(SecondRotationPerSecond * cur_time.second());
	static const QPoint secondHand[4] = {
		QPoint(0, HandWidth / 2),
		QPoint(-2, 0),
		QPoint(0, -SecondHandLength),
		QPoint(2, 0)
	};
	painter->drawConvexPolygon(secondHand, 4);
	painter->restore();
}

void ClockWidget::drawCenterDot(QPainter* painter) {
	painter->save();
	painter->setPen(Qt::NoPen);
	painter->setBrush(Qt::black);
	painter->drawEllipse(QPoint(0, 0), CenterDotRadius, CenterDotRadius);
	painter->restore();
}
