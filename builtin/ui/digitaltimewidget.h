#ifndef DIGITALTIMEWIDGET_H
#define DIGITALTIMEWIDGET_H
#include <QTime>
#include <QWidget>
class ClockWidget;
class DigitalTimeWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DigitalTimeWidget(QWidget *parent = nullptr);
    void            bindClockWidget(ClockWidget* clock);
public slots:
    void            process_time_update(QTime process_time);
protected:
    void            paintEvent(QPaintEvent *event) override;
private:
    QTime           stored_time;
    ClockWidget*    clk_widget;
};

#endif // DIGITALTIMEWIDGET_H
