#ifndef ABOUTMAINWINDOW_H
#define ABOUTMAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class AboutMainWindow;
}
QT_END_NAMESPACE

/**
 * @class AboutMainWindow
 * @brief AboutMainWindow displays information about the application and provides access to related resources.
 *
 * This class represents the main window of the "About" section, showing information, readme content,
 * and other related data.
 */
class AboutMainWindow : public QMainWindow {
    Q_OBJECT

public:
	/**
	 * @brief Constructor for AboutMainWindow.
	 * @param parent The parent widget.
	 */
	AboutMainWindow(QWidget* parent = nullptr);

	/**
	 * @brief Show the main widget.
	 */
	void show_mainWidget();

	/**
	 * @brief Show the readme content.
	 */
	void show_readme();

	/**
	 * @brief Destructor for AboutMainWindow.
	 */
	~AboutMainWindow();

private:
	Ui::AboutMainWindow* ui; ///< The UI object for AboutMainWindow.

	/**
	 * @brief Load runtime data from static information.
	 */
	void load_from_static_info();

	/**
	 * @brief Hide all widgets. Do not invoke this as a standalone action.
	 */
	void hide_all();

	/**
	 * @brief Initialize signal-slot connections.
	 */
	void init_connections();
};

#endif // ABOUTMAINWINDOW_H
