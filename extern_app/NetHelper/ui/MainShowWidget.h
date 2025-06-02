#ifndef MAINSHOWWIDGET_H
#define MAINSHOWWIDGET_H

#include <QWidget>

namespace Ui {
class MainShowWidget;
}

/**
 * @brief The MainShowWidget class. in this application it is placed
 * at one side of the sidebar widgets
 */
class MainShowWidget : public QWidget {
	Q_OBJECT

public:
	/**
	 * @brief MainShowWidget
	 * @param parent
	 */
	explicit MainShowWidget(QWidget* parent = nullptr);
	~MainShowWidget();

	void show_pinger(); ///< show the pinger widget
	void show_scanner(); ///< show the scanner widget
	void show_interfaces(); ///< show the interfaces widget

private:
	Ui::MainShowWidget* ui; ///< ui handle
};

#endif // MAINSHOWWIDGET_H
