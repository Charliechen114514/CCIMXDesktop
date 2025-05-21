#ifndef MEMORYUSAGECHART_H
#define MEMORYUSAGECHART_H
#include "Core/MemoryInfoFetcher.h"
#include <QWidget>

class QChart;
class QPieSeries;

namespace Ui {
class MemoryUsageChart;
}

/**
 * @brief The MemoryUsageChart class
 * The MemoryUsageChart class provides the memory usage chart displaying
 */
class MemoryUsageChart : public QWidget {
	Q_OBJECT

public:
	explicit MemoryUsageChart(QWidget* parent = nullptr);
	~MemoryUsageChart();

public slots:
	/**
	 * @brief flush_ui_once
	 * @param stat
	 * This function is used to flush the memory state from the memory driver
	 */
	void flush_ui_once(const MemoryInfoFetcher::MemoryStat& stat);

private:
	Ui::MemoryUsageChart* ui;
	QChart* physChart;
	QChart* virtChart;
	QPieSeries* physSeries;
	QPieSeries* virtSeries;
	void setup_ui();

	/**
	 * @brief The PackageInfo class
	 * The PackageInfo class provides the package info
	 */
	struct PackageInfo {
		qreal used; ///< used memory
		qreal free; ///< free memory
	};

	void update_charts(QPieSeries* series, const PackageInfo& stat, const QString& label);
	void update_labels(const PackageInfo& virt, const PackageInfo& phy);
};

#endif // MEMORYUSAGECHART_H
