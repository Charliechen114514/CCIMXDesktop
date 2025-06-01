#ifndef MAINSHOWWIDGET_H
#define MAINSHOWWIDGET_H

#include <QWidget>

namespace Ui {
class MainShowWidget;
}

class MainShowWidget : public QWidget {
	Q_OBJECT

public:
	explicit MainShowWidget(QWidget* parent = nullptr);
	~MainShowWidget();

	void show_pinger();
	void show_scanner();
	void show_interfaces();

private:
	Ui::MainShowWidget* ui;
};

#endif // MAINSHOWWIDGET_H
