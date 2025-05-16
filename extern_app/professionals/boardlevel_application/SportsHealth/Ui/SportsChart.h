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

class SportsChart : public QWidget {
	Q_OBJECT

public:
	explicit SportsChart(QWidget* parent = nullptr);
	~SportsChart();

signals:
	void fetch_once_data(const ICM20608AppData data);

public slots:
	/* Request To the Datas */
	void flush_one_request();

private:
	Ui::SportsChart* ui;
	QLineSeries* seriesAx { nullptr };
	QLineSeries* seriesAy { nullptr };
	QLineSeries* seriesAz { nullptr };
	QLineSeries* seriesGx { nullptr };
	QLineSeries* seriesGy { nullptr };
	QLineSeries* seriesGz { nullptr };
	QValueAxis* a_axisX { nullptr };
	QValueAxis* a_axisY { nullptr };
	QValueAxis* g_axisX { nullptr };
	QValueAxis* g_axisY { nullptr };
	QChart* a_chart { nullptr };
	QChart* g_chart { nullptr };
	ICM20608DataFactory factory {};
	QChartView* gChartview { nullptr };
	QChartView* aChartview { nullptr };
	int times_cnt { 0 };
	void allocate_memory();
	void setup_ui();
};

#endif // SPORTSCHART_H
