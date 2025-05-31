#ifndef DOWNDOCKWIDGET_H
#define DOWNDOCKWIDGET_H

#include <QWidget>

namespace Ui {
class DownDockWidget;
}
class DesktopMainWindow;
class AppWidget;

/**
 * @brief The DownDockWidget class holdings the down dock sessions
 * it supports the dynamic sorted according freqency of clicking times
 */
class DownDockWidget : public QWidget {
	Q_OBJECT
	static constexpr unsigned short DOCK_MAX_APP_CNT = 5;

public:
	/**
	 * @brief Construct a new Down Dock Widget object
	 * 
	 * @param parent 
	 */
	explicit DownDockWidget(QWidget* parent = nullptr);
	/**
	 * @brief set_dock_apps set the dock apps waiting for shows
	 * @param apps
	 */
	void set_dock_apps(const QList<AppWidget*>& apps);

	/**
	 * @brief Set the parent window object
	 * 
	 * @param parent_window 
	 */
	void set_parent_window(DesktopMainWindow* parent_window) {
		this->parent_window = parent_window;
	}

	/**
	 * @brief Destroy the Down Dock Widget object
	 * 
	 */
	~DownDockWidget();
	/**
	 * @brief on_app_dispatched hooks the success app
	 * @param app
	 */
	void on_app_dispatched(const AppWidget* app);

private:
	Ui::DownDockWidget* ui;
	QList<AppWidget*> dock_apps;
	QHash<AppWidget*, int> app_usage_count;
	DesktopMainWindow* parent_window { nullptr };
	void replace_docks();
};

#endif // DOWNDOCKWIDGET_H
