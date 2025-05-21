#ifndef DOWNDOCKWIDGET_H
#define DOWNDOCKWIDGET_H

#include <QWidget>

namespace Ui {
class DownDockWidget;
}

class AppWidget;

class DownDockWidget : public QWidget {
	Q_OBJECT

public:
	explicit DownDockWidget(QWidget* parent = nullptr);
	/**
	 * @brief set_dock_apps set the dock apps waiting for shows
	 * @param apps
	 */
	void set_dock_apps(const QList<AppWidget*>& apps);

	~DownDockWidget();

private:
	Ui::DownDockWidget* ui;
	QList<AppWidget*> dock_apps;
	QWidget* internal_widget;
	void replace_docks();
};

#endif // DOWNDOCKWIDGET_H
