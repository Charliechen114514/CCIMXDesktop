#ifndef SPORTSHEALTHWINDOW_H
#define SPORTSHEALTHWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class SportsHealthWindow;
}
QT_END_NAMESPACE

class SportsHealthWindow : public QMainWindow {
	Q_OBJECT

public:
    static constexpr int FLUSH_FREQ = 1000;
	SportsHealthWindow(QWidget* parent = nullptr);
	~SportsHealthWindow();

private:
	Ui::SportsHealthWindow* ui;
};
#endif // SPORTSHEALTHWINDOW_H
