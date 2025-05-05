#include "CPUUsageChart.h"
#include "ui_CPUUsageChart.h"
#include <QChartView>
#include <QLineSeries>
#include <QValueAxis>
void CPUUsageChart::flush_from_cpudriver(const CPUStateFetcher::CPUState& state) {

	double tol = state.kernel + state.user;
	double delta_tol = tol - cached_data.last_tol;
	double delta_idle = state.idle - cached_data.last_idle;
	/* cached the previous one */
	cached_data.last_tol = tol;
	cached_data.last_idle = state.idle;
	/* CPU Usage calculations is specified here */
	double cpu_usage_percentage = (1.0 - delta_idle / delta_tol) * 100.0;
#ifdef QT_DEBUG
	qDebug() << delta_tol << " " << delta_idle;
	qDebug() << tol << " " << state.idle;
	qDebug() << cached_data.last_tol << " " << cached_data.last_idle;
	qDebug() << cpu_usage_percentage;
#endif
	xValues.append(currentTime++);
	yValues.append(cpu_usage_percentage);

	if (xValues.size() > MAX_POINT) {
		xValues.removeFirst();
		yValues.removeFirst();
	}

	series->clear();
	for (int i = 0; i < xValues.size(); ++i)
		series->append(i, yValues[i]);
	flush_labels(state, cpu_usage_percentage);
}

CPUUsageChart::~CPUUsageChart() {
	delete ui;
}

void CPUUsageChart::setup_chart_ui() {
	series = new QLineSeries();
	chart = new QChart();
	chart->legend()->hide();
	chart->addSeries(series);
	chart->setTitle("CPU Usage (%)");

	axisX = new QValueAxis;
	axisX->setRange(0, MAX_POINT);
	axisX->setLabelFormat("%d");
	axisX->setTitleText("Flush Detect Times");
	chart->addAxis(axisX, Qt::AlignBottom);
	series->attachAxis(axisX);

	axisY = new QValueAxis;
	axisY->setRange(0, 100);
	axisY->setTitleText("Usage (%)");
	chart->addAxis(axisY, Qt::AlignLeft);
	series->attachAxis(axisY);

	QChartView* chartView = new QChartView(chart, this);
	chartView->setRenderHint(QPainter::Antialiasing);
	ui->display_chart_widget->layout()->addWidget(chartView);
}

void CPUUsageChart::flush_labels(
	const CPUStateFetcher::CPUState& state, const double cpu_usage_percentage) {
	ui->idle_label->setText("Idel Index: " + QString::number(state.idle));
	ui->kernel_label->setText("Kernel Index: " + QString::number(state.kernel));
	ui->user_label->setText("User Index: " + QString::number(state.user));
	ui->percentage_label->setText("Percentage: " + QString::number(cpu_usage_percentage) + "%");
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

/* QLineSeries（折线图） */
QLineSeries {
    color: #679df6;              /* 设置线条颜色为亮蓝 */
    width: 2px;                  /* 设置线宽 */
    border: 1px solid #8caac0;   /* 设置边框颜色 */
}

/* 鼠标悬停线条的效果 */
QLineSeries:hover {
    color: #4fa3f7;              /* 鼠标悬停时线条变成更亮的蓝色 */
    width: 3px;                  /* 鼠标悬停时增宽线条 */
    border-color: #4fa3f7;       /* 增加悬停时的边框高亮 */
}

/* QLineSeries 数据点（圆点样式） */
QLineSeries::marker {
    border: 2px solid #679df6;   /* 设置圆点边框颜色 */
    background-color: #ffffff;   /* 数据点背景色为白色 */
    width: 6px;                  /* 圆点直径 */
    height: 6px;
    border-radius: 3px;          /* 圆点形状 */
}

/* 鼠标悬停数据点 */
QLineSeries::marker:hover {
    background-color: #4fa3f7;   /* 悬停时数据点变为亮蓝色 */
    border-color: #4fa3f7;       /* 悬停时边框颜色高亮 */
}
)";

CPUUsageChart::CPUUsageChart(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::CPUUsageChart) {
    ui->setupUi(this);
    QHBoxLayout* lays = new QHBoxLayout(ui->display_chart_widget);
    ui->display_chart_widget->setLayout(lays);
    setStyleSheet(chartStyles);
    setup_chart_ui();
}
