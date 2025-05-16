#include "SportsChart.h"
#include "ui_SportsChart.h"
#include <QChartView>
#include <QHBoxLayout>
#include <QLineSeries>
#include <QPainter>
#include <QValueAxis>

SportsChart::SportsChart(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::SportsChart) {
	ui->setupUi(this);
	allocate_memory();
	setup_ui();
}

void SportsChart::allocate_memory() {
	seriesAx = new QLineSeries(this);
	seriesAy = new QLineSeries(this);
	seriesAz = new QLineSeries(this);
	seriesGx = new QLineSeries(this);
	seriesGy = new QLineSeries(this);
	seriesGz = new QLineSeries(this);

	a_axisX = new QValueAxis(this);
	a_axisY = new QValueAxis(this);
	g_axisX = new QValueAxis(this);
	g_axisY = new QValueAxis(this);

	a_chart = new QChart();
	a_chart->addSeries(seriesAx);
	a_chart->addSeries(seriesAy);
	a_chart->addSeries(seriesAz);

	g_chart = new QChart();
	g_chart->addSeries(seriesGx);
	g_chart->addSeries(seriesGy);
	g_chart->addSeries(seriesGz);

	a_axisX->setRange(0, 100);
	a_axisY->setRange(G_MIN_VAL, G_MAX_VAL);

	g_axisX->setRange(0, 100);
	g_axisY->setRange(ROL_MIN_VAL, ROL_MAX_VAL);

	a_chart->addAxis(a_axisX, Qt::AlignBottom);
	a_chart->addAxis(a_axisY, Qt::AlignLeft);

	g_chart->addAxis(g_axisX, Qt::AlignBottom);
	g_chart->addAxis(g_axisY, Qt::AlignLeft);

	seriesAx->attachAxis(a_axisX);
	seriesAx->attachAxis(a_axisY);
	seriesAy->attachAxis(a_axisX);
	seriesAy->attachAxis(a_axisY);
	seriesAz->attachAxis(a_axisX);
	seriesAz->attachAxis(a_axisY);

	seriesGx->attachAxis(g_axisX);
	seriesGx->attachAxis(g_axisY);
	seriesGy->attachAxis(g_axisX);
	seriesGy->attachAxis(g_axisY);
	seriesGz->attachAxis(g_axisX);
	seriesGz->attachAxis(g_axisX);
}

/* srtup the display issue */
void SportsChart::setup_ui() {
	seriesAx->setName("Accel X");
	seriesAy->setName("Accel Y");
	seriesAz->setName("Accel Z");
	seriesGx->setName("Gyro X");
	seriesGy->setName("Gyro Y");
	seriesGz->setName("Gyro Z");
	a_axisX->setTitleText("Times");
	a_axisX->setRange(0, 10);
	g_axisX->setTitleText("Times");
	g_axisX->setRange(0, 10);

	aChartview = new QChartView(a_chart, this);
	aChartview->setRenderHint(QPainter::Antialiasing);

	gChartview = new QChartView(g_chart, this);
	gChartview->setRenderHint(QPainter::Antialiasing);

	QHBoxLayout* layout = new QHBoxLayout(this);
	setLayout(layout);

	layout->addWidget(aChartview);
	layout->addWidget(gChartview);
}

SportsChart::~SportsChart() {
	delete ui;
}

void SportsChart::flush_one_request() {
	ICM20608AppData data {};
	factory.get_package_sync(data);
	emit fetch_once_data(data);
	qDebug() << "g_acc: " << data.g_acc.x << data.g_acc.y << data.g_acc.z;
	qDebug() << "rol: " << data.rol.x << data.rol.y << data.rol.z;
	times_cnt++;
	seriesAx->append(times_cnt, data.g_acc.x);
	seriesAy->append(times_cnt, data.g_acc.y);
	seriesAz->append(times_cnt, data.g_acc.z);
	seriesGx->append(times_cnt, data.rol.x);
	seriesGy->append(times_cnt, data.rol.y);
	seriesGz->append(times_cnt, data.rol.z);
	/* remove the old data */
	while (!seriesAx->points().isEmpty()
		   && seriesAx->points().first().x() < times_cnt - 10) {
		seriesAx->remove(0);
		seriesAy->remove(0);
		seriesAz->remove(0);
	}

	while (!seriesGx->points().isEmpty()
		   && seriesGx->points().first().x() < times_cnt - 10) {
		seriesGx->remove(0);
		seriesGy->remove(0);
		seriesGz->remove(0);
	}

	a_axisX->setRange(qMax(0, times_cnt - 10), times_cnt);
	g_axisX->setRange(qMax(0, times_cnt - 10), times_cnt);
}
