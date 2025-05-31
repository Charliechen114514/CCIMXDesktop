#ifndef ABOUTMAINWINDOW_H
#define ABOUTMAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class AboutMainWindow;
}
QT_END_NAMESPACE

class AboutMainWindow : public QMainWindow {
	Q_OBJECT

public:
	AboutMainWindow(QWidget* parent = nullptr);
	void show_mainWidget();
	void show_readme();
	~AboutMainWindow();

private:
	Ui::AboutMainWindow* ui;
	void load_from_static_info();
	void hide_all();
	void init_connections();
};
#endif // ABOUTMAINWINDOW_H
