#ifndef SPORTSCHART_H
#define SPORTSCHART_H

#include "ICM20608DataFactory.h"
#include <QWidget>

class QLineSeries;
class QValueAxis;
class QTimer;
class QChart;
class QChartView;

namespace Ui {
class SportsChart;
}

/**
 * @class SportsChart
 * @brief Widget for displaying sports sensor data charts.
 *
 * This widget fetches data from the ICM20608 sensor via the data factory,
 * and displays acceleration and rotation data over time using Qt Charts.
 */
class SportsChart : public QWidget {
    Q_OBJECT

public:
	/**
	 * @brief Constructs the SportsChart widget.
	 * @param parent Parent widget pointer.
	 */
	explicit SportsChart(QWidget* parent = nullptr);

	/**
	 * @brief Destructor for SportsChart.
	 */
	~SportsChart();

signals:
	/**
	 * @brief Signal emitted when new sensor data is fetched.
	 * @param data The ICM20608 sensor data.
	 */
	void fetch_once_data(const ICM20608AppData data);

public slots:
	/**
	 * @brief Request one data sample update from the sensor.
	 */
	void flush_one_request();

private:
	Ui::SportsChart* ui;

	QLineSeries* seriesAx { nullptr }; ///< Series for acceleration X axis data
	QLineSeries* seriesAy { nullptr }; ///< Series for acceleration Y axis data
	QLineSeries* seriesAz { nullptr }; ///< Series for acceleration Z axis data

	QLineSeries* seriesGx { nullptr }; ///< Series for gyroscope X axis data
	QLineSeries* seriesGy { nullptr }; ///< Series for gyroscope Y axis data
	QLineSeries* seriesGz { nullptr }; ///< Series for gyroscope Z axis data

	QValueAxis* a_axisX { nullptr }; ///< X axis for acceleration chart
	QValueAxis* a_axisY { nullptr }; ///< Y axis for acceleration chart
	QValueAxis* g_axisX { nullptr }; ///< X axis for gyroscope chart
	QValueAxis* g_axisY { nullptr }; ///< Y axis for gyroscope chart

	QChart* a_chart { nullptr }; ///< Acceleration chart
	QChart* g_chart { nullptr }; ///< Gyroscope chart

	ICM20608DataFactory factory {}; ///< Sensor data factory

	QChartView* gChartview { nullptr }; ///< View for gyroscope chart
	QChartView* aChartview { nullptr }; ///< View for acceleration chart

	int times_cnt { 0 }; ///< Counter for number of data fetches

	/**
	 * @brief Allocate dynamic memory or initialize members.
	 */
	void allocate_memory();

	/**
	 * @brief Setup UI components and charts.
	 */
	void setup_ui();
};

#endif // SPORTSCHART_H
