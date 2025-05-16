#ifndef SPORTSDISPLAYWIDGET_H
#define SPORTSDISPLAYWIDGET_H
#include "ICM20608Data.h"
#include <QWidget>

namespace Ui {
class SportsDisplayWidget;
}

class SportsDisplayWidget : public QWidget {
	Q_OBJECT

public:
	explicit SportsDisplayWidget(QWidget* parent = nullptr);
	~SportsDisplayWidget();

public slots:
	void setDisplay(const ICM20608AppData& data);

private:
	Ui::SportsDisplayWidget* ui;
};

#endif // SPORTSDISPLAYWIDGET_H
