#ifndef MEMORYUSAGECHART_H
#define MEMORYUSAGECHART_H
#include "Core/MemoryInfoFetcher.h"
#include <QWidget>

class QChart;
class QPieSeries;

namespace Ui {
class MemoryUsageChart;
}

class MemoryUsageChart : public QWidget {
	Q_OBJECT

public:
	explicit MemoryUsageChart(QWidget* parent = nullptr);
	~MemoryUsageChart();

public slots:
	void flush_ui_once(const MemoryInfoFetcher::MemoryStat& stat);

private:
	Ui::MemoryUsageChart* ui;
	QChart* physChart;
	QChart* virtChart;
	QPieSeries* physSeries;
	QPieSeries* virtSeries;
	void setup_ui();
	struct PackageInfo {
		qreal used;
		qreal free;
	};

	void update_charts(QPieSeries* series, const PackageInfo& stat, const QString& label);
	void update_labels(const PackageInfo& virt, const PackageInfo& phy);
};

#endif // MEMORYUSAGECHART_H
