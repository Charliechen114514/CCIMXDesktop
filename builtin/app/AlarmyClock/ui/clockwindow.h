#ifndef CLOCKWINDOW_H
#define CLOCKWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class ClockWindow;
}
QT_END_NAMESPACE
class ClockWidget;
class ClockEventBroadcaster;
class GlobalTimerSrc;
class TimerCreatorWindow;
class AlarmyNotifier;
class ToolsBar;
class ClockWindow : public QMainWindow {
	Q_OBJECT

public:
    ClockWindow(QWidget* parent = nullptr);
	~ClockWindow();

public slots:
    void popup_create_window();


private:
    Ui::ClockWindow* ui;
    GlobalTimerSrc* global_src{nullptr};
    ClockWidget* clockWidget;
    TimerCreatorWindow* creator_window{nullptr};
    AlarmyNotifier* notifier{nullptr};
	ClockEventBroadcaster* broadcaster { nullptr };
    ToolsBar* toolBar{nullptr};
private:
    void init_core();
    void init_window();
    void init_connection();
};
#endif // CLOCKWINDOW_H
