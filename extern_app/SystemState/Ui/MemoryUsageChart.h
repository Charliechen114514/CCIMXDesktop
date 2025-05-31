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
	/**
	 * @brief Construct a new Memory Usage Chart object
	 * 
	 * @param parent 
	 */
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
	QChart* physChart; ///< physChart
	QChart* virtChart; ///< virtChart
	QPieSeries* physSeries; ///< physSeries
	QPieSeries* virtSeries; ///< virtSeries
	/**
	 * @brief Set the up ui object
	 * 
	 */
	void setup_ui();

	/**
	 * @brief The PackageInfo class
	 * The PackageInfo class provides the package info
	 */
	struct PackageInfo {
		qreal used; ///< used memory
		qreal free; ///< free memory
	};
	/**
	 * @brief update_charts
	 * 
	 * @param series 
	 * @param stat 
	 * @param label 
	 */
	void update_charts(QPieSeries* series, const PackageInfo& stat, const QString& label);
	/**
	 * @brief update display labels
	 * 
	 * @param virt 
	 * @param phy 
	 */
	void update_labels(const PackageInfo& virt, const PackageInfo& phy);
};

#endif // MEMORYUSAGECHART_H
