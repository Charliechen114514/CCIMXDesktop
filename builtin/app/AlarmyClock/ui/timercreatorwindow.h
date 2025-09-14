#ifndef TIMERCREATORWINDOW_H
#define TIMERCREATORWINDOW_H

#include <QMainWindow>
class AlarmyNote;


class TimerCreatorWindow : public QMainWindow {
	Q_OBJECT
public:
    explicit TimerCreatorWindow(QWidget* parent = nullptr);

signals:
    void notifyNewTimer(AlarmyNote* alarmy_notes);
};

#endif // TIMERCREATORWINDOW_H
