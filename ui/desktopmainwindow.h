#ifndef DESKTOPMAINWINDOW_H
#define DESKTOPMAINWINDOW_H

#include "ui/appwidget.h"
#include <QMainWindow>
QT_BEGIN_NAMESPACE
namespace Ui {
class DesktopMainWindow;
}
QT_END_NAMESPACE
/* App layouts */
class QGridLayout;
class QLabel;
class DesktopToast;
class ApplicationWrapper;
class QTimer;
class QStackedWidget;
class DownDockWidget;
class AppCardWidget;

/**
 * @brief DesktopMainWindow Makes the total front end of everything,
 * for beginners, you can start at here to see the details
 */
class DesktopMainWindow : public QMainWindow {
    Q_OBJECT

public:
	friend class PageFactory;
	struct WallPaperGroup {
		/**
		 * @brief This means the widget should be lower in animations,
		 * typically, this is the centralwidget of the window
		 */
		QWidget* shoule_be_lower;
		/**
		 * @brief wallpaperLabel is a wall paper label is using in display the current
		 */
		QLabel* wallpaperLabel { nullptr };
		/**
		 * @brief bufferpaperLabel helps the animations
		 */
		QLabel* bufferpaperLabel { nullptr };
		/**
		 * @brief this is using in switch, any switch interval behaviour
		 */
		QTimer* invoke_switch_timer;
	};

	DesktopMainWindow(QWidget* parent = nullptr);
	/**
	 * @brief This is using in showing some toasts in the mainwindow
	 * @param message for posting
	 */
	void showToast(const QString& message);
	/**
	 * @brief returns the DesktopToast Handle
	 * @return DesktopToast
	 */
	inline DesktopToast* desktop_toast() const { return toast; }

	/**
	 * @brief downDockWidget returns the global instance of the downDockWidget
	 * @return DownDockWidget
	 */
	DownDockWidget* downDockWidget() const;

	/**
	 * @brief to_next_page makes the slide to next page
	 */
	void to_next_page();
	/**
	 * @brief to_prev_page makes the slide to previous page
	 */
	void to_prev_page();
	~DesktopMainWindow();
	/**
	 * @brief invoke this can depatch a session of page switching
	 */
	void invoke_switch_bgpage();
	/**
	 * @brief install_remote_appwrapper installs a remote app wrapper
	 * @param wrapper the wrapper to be installed
	 */
	void inline install_remote_appwrapper(ApplicationWrapper* wrapper) { app_wrapper << wrapper; }
	/**
	 * @brief handle_app_status is the handler for app status, it will
	 * be called when the app status is changed, like the app depatching errors
	 * @param status: the status waiting for the depatching
	 */
	void handle_app_status(AppWidget::AppStatus status);
	/**
	 * @brief returns the stackedWidget the slider using
	 * @return QStackedWidget
	 */
	QStackedWidget* stackedWidget() const;
	/**
	 * @brief post_show makes the later init of the mainWindow
	 */
	void post_show();
signals:
	/**
	 * @brief Signals, that when everytime the app cards
	 * requires init, the signals is triggered
	 */
	void deptach_app_cards_init();

protected:
	void mousePressEvent(QMouseEvent* event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;
	void resizeEvent(QResizeEvent* event) override;

private:
	Ui::DesktopMainWindow* ui;
	DesktopToast* toast;
	QList<ApplicationWrapper*> app_wrapper;
	QList<AppWidget*> app_widgets;

	WallPaperGroup wallPaperGroup;
	QStringList image_lists;

	struct {
		QPoint press; ///< where do you press?
		QPoint release; ///< where do you release?
	} records; ///< using in detect the mouse pos, and shell be used in <- ->

	static constexpr const unsigned int switch_bg_time = 20000;

	/* Appcards */
	QList<AppCardWidget*> app_cards;

	/**
	 * @brief post_setupui is the post setup UI function,
	 *  after the ui->setupUi(), we still need to further map
	 *  the ui elements
	 */
	void post_setupui();
	/**
	 * @brief setup_bg_image is the background setup function
	 */
	void setup_bg_image();
	/**
	 * @brief setup_apps makes the app setup internally,
	 * including some default apps ready
	 */
	void setup_apps();

	/**
	 * @brief invoke_appcards_init, defaultly, signal
	 * deptach_app_cards_init triiger the slots
	 */
	void invoke_appcards_init();
};
#endif // DESKTOPMAINWINDOW_H
