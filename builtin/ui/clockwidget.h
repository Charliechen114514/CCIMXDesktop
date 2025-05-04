#ifndef CLOCKWIDGET_H
#define CLOCKWIDGET_H
#include <QTime>
#include <QWidget>

namespace Ui {
class ClockWidget;
}
class QTimer;

class ClockWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ClockWidget(QWidget *parent = nullptr);
    ~ClockWidget();

signals:
    /* for other clock relavent widgets, should monitor the signals */
    void    time_update(QTime time);
protected:
    /* Yep, for the dynamic widgets, we have to, sadly, draw by ourselves */
    /* Entry for us to draw a clock */
    void paintEvent(QPaintEvent* _paintEvent) override;
    QSize sizeHint() const override;
private:

    // Constants
    static constexpr const int DefaultWidgetSize = 1000;
    static constexpr const int DialSize = 200;
    static constexpr const int OuterCircleRadius = 95;
    static constexpr const int HourTickLength = 10;
    static constexpr const int MinuteTickLength = 5;
    static constexpr const int HourTickWidth = 2;
    static constexpr const int MinuteTickWidth = 1;
    static constexpr const int CenterDotRadius = 4;
    static constexpr const int HourHandLength = 50;
    static constexpr const int MinuteHandLength = 70;
    static constexpr const int SecondHandLength = 80;
    static constexpr const int HandWidth = 7;
    static constexpr const int HourRotationPerHour = 30;    // 360 / 12
    static constexpr const int MinuteRotationPerMinute = 6; // 360 / 60
    static constexpr const int SecondRotationPerSecond = 6; // 360 / 60

    /* fonts */
    static constexpr const int NumberDistanceFromCenter = 70;
    static constexpr const int NumberFontSize = 14;
    Ui::ClockWidget *ui;
    /* internal updater is trying to update the clock apperance timely */
    QTimer*         internal_updater;
    QTime           cur_time;
    /* for internal_updater's timeout, it's the function handle */
    void            process_update_invokation();
    /* paintEvent periodly and invoke the funcList in sequence */
    void            drawBackground(QPainter *painter);
    void            drawTicks(QPainter *painter);
    void            drawHands(QPainter *painter);
    void            drawNumbers(QPainter *painter);
    void            drawCenterDot(QPainter *painter);
};

#endif // CLOCKWIDGET_H
