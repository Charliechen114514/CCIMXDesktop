#include "MemoryUsageChart.h"
#include "ui_MemoryUsageChart.h"
#include <QChart>
#include <QChartView>
#include <QPieSeries>

MemoryUsageChart::~MemoryUsageChart() {
	delete ui;
}

void MemoryUsageChart::flush_ui_once(const MemoryInfoFetcher::MemoryStat& stat) {

	/* phy issue */
	PackageInfo phy {
		static_cast<qreal>(
			stat.total_phys_memory - stat.avail_phys_memory),
		static_cast<qreal>(stat.avail_phys_memory),
	};
	update_charts(physSeries, phy, "Physical Memory");
	/* virt issue */
	qreal avai_virt = stat.avail_virt_memory / 1024.0 / 1024.0 / 1024.0;
	qreal tol_virt = stat.total_virt_memory / 1024.0 / 1024.0 / 1024.0;
	PackageInfo virt { tol_virt - avai_virt, avai_virt };
	update_charts(virtSeries, virt, "Virtual Memory");
	update_labels(virt, phy);
}

void MemoryUsageChart::setup_ui() {
	physSeries = new QPieSeries();
	virtSeries = new QPieSeries();

	physChart = new QChart();
	physChart->addSeries(physSeries);
	physChart->setTitle("Physical Memory Usage");
	physChart->legend()->setAlignment(Qt::AlignBottom);

	virtChart = new QChart();
	virtChart->addSeries(virtSeries);
	virtChart->setTitle("Virtual Memory Usage");
	virtChart->legend()->setAlignment(Qt::AlignBottom);

	QChartView* physView = new QChartView(physChart);
	QChartView* virtView = new QChartView(virtChart);

	physView->setRenderHint(QPainter::Antialiasing);
	virtView->setRenderHint(QPainter::Antialiasing);

	ui->display_widget->layout()->addWidget(physView);
	ui->display_widget->layout()->addWidget(virtView);
}

void MemoryUsageChart::
    update_charts(QPieSeries* series,
                  const PackageInfo& stat,
                  const QString& label) {
    series->clear();

	series->append("Used", stat.used);
	series->append("Free", stat.free);
	auto result = series->slices();
	for (QPieSlice* slice : std::as_const(result)) {
		if (slice->label().contains("Used")) {
			slice->setBrush(Qt::red);
			slice->setExploded(true);
		} else {
			slice->setBrush(Qt::green);
		}
	}
}

void MemoryUsageChart::update_labels(const PackageInfo& virt, const PackageInfo& phy) {

	ui->virtual_available_label->setText(
		"Virtual Memory avaiable: " + QString::number(virt.free) + "GB");

	ui->virtual_tol_label->setText(
		"Virtual Memory total: " + QString::number(virt.used + virt.free) + "GB");

	double percentage = 1 / (1 + virt.free / virt.used) * 100.0;
	ui->virtual_percentage_label->setText(
		"Virtual Memory usage percentage: " + QString::number(percentage, 'f', 2) + "%");

	ui->phy_avail_label->setText(
		"Physical Memory avaiable: " + MemoryInfoFetcher::format_size(phy.free));

	ui->phy_total_label->setText(
		"Physical Memory total: " + MemoryInfoFetcher::format_size(phy.used + phy.free));

	percentage = (phy.used / (phy.used + phy.free)) * 100.0;
	ui->phy_percentage->setText(
		"Physical Memory usage percentage: " + QString::number(percentage, 'f', 2) + "%");
}

static constexpr const char* chartStyles = R"(
/* QChartView 样式 */
QChartView {
    background-color: #e6f0fa;
    border: 1px solid #8caac0;
    border-radius: 6px;
}
QChartView > QGraphicsWidget {
    padding: 0px;
    margin: 0px;
}

/* 图例样式 */
QLegend {
    background-color: rgba(255,255,255,180);
    border: 1px solid #8caac0;
    border-radius: 4px;
    color: #1e1e2e;
    font-size: 8pt;
}
QLegend::marker {
    width: 12px; height: 12px;
    border: 1px solid #8caac0;
    border-radius: 2px;
}
QLegend::marker:selected {
    background-color: #8ab4f8;
    border-color: #679df6;
}

/* 饼图样式 */
QPieSlice {
    border: 1px solid #b0c4d6;
    border-radius: 2px;
}
QPieSlice:hover {
    exploded: true;
    explosion-distance-factor: 0.1;
}

/* 扇区颜色 */
QPieSlice:nth-child(1) { background-color: #679df6; }  /* Used */
QPieSlice:nth-child(2) { background-color: #c1e1c5; }  /* Free */

/* 标签样式 */
QPieSlice QLabel {
    color: #1e1e2e;
    font-size: 8pt;
    background: transparent;
}
)";

MemoryUsageChart::MemoryUsageChart(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::MemoryUsageChart) {
    ui->setupUi(this);
    QHBoxLayout* box = new QHBoxLayout(this);
    ui->display_widget->setLayout(box);
    setStyleSheet(chartStyles);
    setup_ui();
}
