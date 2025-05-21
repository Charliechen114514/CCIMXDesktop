#ifndef CPUUSAGECHART_H
#define CPUUSAGECHART_H
#include "Core/CPUStateFetcher.h"
#include <QWidget>
class QChart;
class QLineSeries;
class QValueAxis;

namespace Ui {
class CPUUsageChart;
}

/**
 * @brief The CPUUsageChart class
 * The CPU UsageChart class provides the CPU usage chart displaying
 */
class CPUUsageChart : public QWidget {
	Q_OBJECT

public:
	explicit CPUUsageChart(QWidget* parent = nullptr);
	~CPUUsageChart();

public slots:
	/**
	 * @brief flush_from_cpudriver
	 * @param state
	 * This function is used to flush the CPU state from the CPU driver
	 */
	void flush_from_cpudriver(const CPUStateFetcher::CPUState& state);

private:
	static constexpr const unsigned short MAX_POINT { 30 };
	void setup_chart_ui();
	void flush_labels(const CPUStateFetcher::CPUState& state, const double cpu_usage_percentage);
	Ui::CPUUsageChart* ui;
	QChart* chart { nullptr };
	QLineSeries* series { nullptr };
	QValueAxis* axisX { nullptr };
	QValueAxis* axisY { nullptr };
	QList<int> xValues;
	QList<double> yValues;
	int currentTime = 0; ///< current boarding time
	struct {
		double last_tol { 0.0 }; ///< last total time
		double last_idle { 0.0 }; ///< last idle time
	} cached_data; ///< cached data for calculate the usage percentage
};

#endif // CPUUSAGECHART_H
