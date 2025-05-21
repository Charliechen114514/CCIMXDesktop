#ifndef SPORTSDISPLAYWIDGET_H
#define SPORTSDISPLAYWIDGET_H

#include "ICM20608Data.h"
#include <QWidget>

namespace Ui {
class SportsDisplayWidget;
}

/**
 * @class SportsDisplayWidget
 * @brief Widget to display current sports sensor data values.
 *
 * This widget shows the current acceleration and gyroscope data
 * received from the sensor.
 */
class SportsDisplayWidget : public QWidget {
    Q_OBJECT

public:
	/**
	 * @brief Constructs the SportsDisplayWidget.
	 * @param parent Parent widget pointer.
	 */
	explicit SportsDisplayWidget(QWidget* parent = nullptr);

	/**
	 * @brief Destructor for SportsDisplayWidget.
	 */
	~SportsDisplayWidget();

public slots:
	/**
	 * @brief Update the displayed data.
	 * @param data New sensor data to display.
	 */
	void setDisplay(const ICM20608AppData& data);

private:
	Ui::SportsDisplayWidget* ui;
};

#endif // SPORTSDISPLAYWIDGET_H
