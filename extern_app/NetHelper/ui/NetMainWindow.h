#ifndef NETMAINWINDOW_H
#define NETMAINWINDOW_H

#include <QMainWindow>
class ToolBoxs;
class MainShowWidget;
QT_BEGIN_NAMESPACE
namespace Ui {
class NetMainWindow;
}
QT_END_NAMESPACE

/**
 * @brief The NetMainWindow class
 */
class NetMainWindow : public QMainWindow {
	Q_OBJECT

public:
	NetMainWindow(QWidget* parent = nullptr);
	~NetMainWindow();

protected:
	void resizeEvent(QResizeEvent*);

private:
	Ui::NetMainWindow* ui;
	ToolBoxs* toolbox;
	MainShowWidget* mainWidget;
	void flipSideBar();
	bool sideBarShow { true };
};
#endif // NETMAINWINDOW_H
