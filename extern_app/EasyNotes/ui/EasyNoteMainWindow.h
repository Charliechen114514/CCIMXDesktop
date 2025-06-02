#ifndef EASYNOTEMAINWINDOW_H
#define EASYNOTEMAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class EasyNoteMainWindow;
}
QT_END_NAMESPACE
class LeftSideBar;
class MainSideBar;
/**
 * @brief The EasyNoteMainWindow class
 * is the mainWindow
 */
class EasyNoteMainWindow : public QMainWindow {
	Q_OBJECT

public:
	/**
 	* @brief Construct a new Easy Note Main Window object
 	* 
 	* @param parent 
 	*/
	EasyNoteMainWindow(QWidget* parent = nullptr);
	~EasyNoteMainWindow();

private:
	Ui::EasyNoteMainWindow* ui; ///< ui handler
	LeftSideBar* left; ///< left sidebar
	MainSideBar* mainSideBar; ///< main sidebar

	void init_connections();
};
#endif // EASYNOTEMAINWINDOW_H
