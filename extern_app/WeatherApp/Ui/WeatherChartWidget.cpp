#include "WeatherChartWidget.h"
#include "StackPageSwitcher.h"
#include "ui_WeatherChartWidget.h"
WeatherChartWidget::WeatherChartWidget(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::WeatherChartWidget) {
    ui->setupUi(this);
    connect(ui->btn_mainpage, &QPushButton::clicked, this, [this]() { switch_to_page(Page::MAIN_PAGE); });
    connect(ui->btn_high_temp, &QPushButton::clicked, this, [this]() { switch_to_page(Page::HIGH_TEMP); });
    connect(ui->btn_lowtemp, &QPushButton::clicked, this, [this]() { switch_to_page(Page::LOW_TEMP); });
    connect(ui->btn_humidity, &QPushButton::clicked, this, [this]() { switch_to_page(Page::HUMIDITY); });
    connect(ui->btn_windscale, &QPushButton::clicked, this, [this]() { switch_to_page(Page::WINDSCALE); });
}

void WeatherChartWidget::
    fresh_display(
        QList<AppWeatherResult::DailyWeather>& weathers) {
    /* old sessions */
    for (int i = ui->stackedWidget->count() - 1; i >= 0; i--) {
        QWidget* widget = ui->stackedWidget->widget(i);
        ui->stackedWidget->removeWidget(widget);
        widget->deleteLater();
    }
    makeup_mainpage(weathers);
    makeup_chart(weathers, "Highest Temp(℃)", [](const AppWeatherResult::DailyWeather& d) { return d.high.toInt(); });
    makeup_chart(weathers, "Lowest Temp(℃)", [](const AppWeatherResult::DailyWeather& d) { return d.low.toInt(); });
    makeup_chart(weathers, "Wind Level", [](const AppWeatherResult::DailyWeather& d) { return d.windScale.toInt(); });
    makeup_chart(weathers, "Humidity (%)", [](const AppWeatherResult::DailyWeather& d) { return d.humidity.toInt(); });
}

void WeatherChartWidget::switch_to_page(const Page& p) {
	int currentIndex = ui->stackedWidget->currentIndex();
	if (currentIndex < 0 || currentIndex == index)
		return;

	StackpageSwitcherAnimation::AnimationInfo info;
	info.new_index = static_cast<int>(p);
	info.toLeft = (currentIndex < info.new_index);
	StackpageSwitcherAnimation::process_animations(ui->stackedWidget, &info);
}

WeatherChartWidget::~WeatherChartWidget() {
	delete ui;
}

void WeatherChartWidget::makeup_chart(
    const QList<AppWeatherResult::DailyWeather>& data,
    const QString& title,
    FromDailySession sessionfunc) {
    QLineSeries* current_sessions = new QLineSeries(this);
    QStringList categories;
    int index = 0;
    int maxY = 0;
    int minY = INT_MAX;

	for (const AppWeatherResult::DailyWeather& d : data) {
		int value = sessionfunc(d);
		maxY = std::max(maxY, value);
		minY = std::min(minY, value);
		current_sessions->append(index, value);
		categories << d.date.mid(5);
		++index;
	}

	QChart* chart = new QChart;
	chart->addSeries(current_sessions);
	chart->setTitle(title);
	chart->legend()->hide();

	QCategoryAxis* axisX = new QCategoryAxis;
	for (int i = 0; i < categories.size(); ++i)
		axisX->append(categories[i], i);
	axisX->setLabelsPosition(QCategoryAxis::AxisLabelsPositionOnValue);
	chart->addAxis(axisX, Qt::AlignBottom);
	current_sessions->attachAxis(axisX);

	QValueAxis* axisY = new QValueAxis;
	axisY->setRange(minY - 1, maxY + 5);
	chart->addAxis(axisY, Qt::AlignLeft);
	current_sessions->attachAxis(axisY);

	QChartView* chartView = new QChartView(chart);
	chartView->setRenderHint(QPainter::Antialiasing);
	/* do as the grid level */
	QGridLayout* l = new QGridLayout(chartView);
	chartView->setLayout(l);
	ui->stackedWidget->addWidget(chartView);

	chart->setTheme(QChart::ChartThemeLight);
	chart->setBackgroundBrush(QBrush(QColor(231, 244, 251)));
	chart->setPlotAreaBackgroundBrush(QBrush(QColor(255, 255, 255)));
	chart->setPlotAreaBackgroundVisible(true);

	QFont titleFont;
	titleFont.setPointSize(14);
	titleFont.setBold(true);
	chart->setTitleFont(titleFont);
	chart->setTitleBrush(QBrush(QColor(46, 60, 77)));

	QPen axisPen(QColor(135, 206, 235));
	QFont labelFont("Microsoft YaHei", 10);
	/* I intended to do this, we must make a copy instead of borrow :) */
	const auto h_first = chart->axes(Qt::Horizontal).first();
	const auto v_first = chart->axes(Qt::Vertical).first();

	h_first->setLabelsFont(labelFont);
	v_first->setLabelsFont(labelFont);
	h_first->setLinePen(axisPen);
	v_first->setLinePen(axisPen);
	h_first->setLabelsBrush(QBrush(QColor(46, 60, 77)));
	v_first->setLabelsBrush(QBrush(QColor(46, 60, 77)));

	QLegend* chartLegent = chart->legend();
	chartLegent->setVisible(true);
	chartLegent->setAlignment(Qt::AlignTop);
	chartLegent->setLabelColor(QColor(46, 60, 77));
	chartLegent->setFont(QFont("Microsoft YaHei", 10));
}

#include "WeatherDailyCard.h"
void WeatherChartWidget::
    makeup_mainpage(
        const QList<AppWeatherResult::DailyWeather>& data) {

	QWidget* mainPage = new QWidget(this);
	QHBoxLayout* l = new QHBoxLayout(mainPage);
	mainPage->setLayout(l);
	for (const auto& each : data) {
		WeatherDailyCard* card = new WeatherDailyCard(mainPage);
		card->bind_daily_info(each);
		l->addWidget(card);
	}

	ui->stackedWidget->addWidget(mainPage);
}
