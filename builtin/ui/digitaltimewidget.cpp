#include "digitaltimewidget.h"
#include "clockwidget.h"
#include <QPainter>
DigitalTimeWidget::DigitalTimeWidget(QWidget *parent)
    : QWidget{parent}
{
    this->stored_time = QTime::currentTime();
}

void DigitalTimeWidget::bindClockWidget(ClockWidget *clock)
{
    clk_widget = clock;
    connect(clk_widget, &ClockWidget::time_update,
            this, &DigitalTimeWidget::process_time_update);
}

void DigitalTimeWidget::process_time_update(QTime process_time)
{
    update();
}

void DigitalTimeWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::NoBrush);

    QTime time = QTime::currentTime();
    QString timeText = time.toString("hh:mm:ss");

    QDate date = QDate::currentDate();
    QString dateText = date.toString("yyyy MMM dd ddd");

    QFont font("Helvetica Neue", 40, QFont::Bold);
    painter.setFont(font);

    QRect textRect = rect();
    painter.setPen(QColor(255, 255, 255));
    painter.drawText(textRect, Qt::AlignCenter, timeText);

    QFont dateFont("Helvetica Neue", 15, QFont::Light);
    painter.setFont(dateFont);
    QRect dateRect = rect();
    dateRect.moveTop(textRect.bottom() - 150);
    painter.setPen(QColor(255, 255, 255));
    painter.drawText(dateRect, Qt::AlignCenter, dateText);
}
