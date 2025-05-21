#ifndef APPCARDWIDGET_H
#define APPCARDWIDGET_H

#include <QWidget>

class DesktopToast;

namespace Ui {
class AppCardWidget;
}

/* App Card Widgets is simple lighted widget that is
 * only post messages to the Toast
 */
class AppCardWidget : public QWidget {
    Q_OBJECT

public:
	Q_DISABLE_COPY(AppCardWidget);
	AppCardWidget() = delete;
	explicit AppCardWidget(DesktopToast* toast, QWidget* parent = nullptr);

	/* Icons for the current */

	/**
	 * @brief setCurrentIcon: for app cards, if we wanna specify the
	 * icons, we can use this function to rewrite the concrete app icons
	 * settings behaviors
	 * @param icons indicates the raw pixmaps we wanna using as a pixmaps
	 */
	virtual void setCurrentIcon(const QPixmap& icons);

	/**
	 * @brief invoke_preLaunch_work is the main function to invoke the prelaunching issue
	 * @note when system starts, app cards are supposed to do their actions
	 * and if not, then do nothing
	 */
	virtual void invoke_preLaunch_work(void) = 0;

	~AppCardWidget();

protected:
	/**
	 * @brief postAppCardWidget, sometimes, we can use this to post the
	 * messages to the binding_toast
	 */
	virtual void postAppCardWidget() = 0;
	DesktopToast* binding_toast;
	Ui::AppCardWidget* ui;

public:
	/**
	 * @brief defines how to listen to the user interactive events
	 * @param watched which objects?
	 * @param event what event?
	 * @return if handles, return true
	 */
	bool eventFilter(QObject* watched, QEvent* event) override;
};

#endif // APPCARDWIDGET_H
