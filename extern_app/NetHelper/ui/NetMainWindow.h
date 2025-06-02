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
	/**
	 * @brief NetMainWindow
	 * @param parent
	 */
	NetMainWindow(QWidget* parent = nullptr);
	~NetMainWindow();

private:
	Ui::NetMainWindow* ui; ///< ui hanlde
	ToolBoxs* toolbox; ///< toolbox
	MainShowWidget* mainWidget; ///< main show widget
	bool sideBarShow { true }; ///< sidebar show flags
	/**
	 * @brief flipSideBar flip the sidebar show issue
	 */
	void flipSideBar();
};
#endif // NETMAINWINDOW_H
