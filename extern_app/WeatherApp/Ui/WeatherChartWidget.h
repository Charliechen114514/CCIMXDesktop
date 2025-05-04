#ifndef WEATHERCHARTWIDGET_H
#define WEATHERCHARTWIDGET_H

#include "AppWeatherRequest.h"
#include <QWidget>
#include <QtCharts>
namespace Ui {
class WeatherChartWidget;
}

class WeatherChartWidget : public QWidget {
	Q_OBJECT

public:
	enum Page {
		MAIN_PAGE,
		HIGH_TEMP,
		LOW_TEMP,
		WINDSCALE,
		HUMIDITY
	};

	explicit WeatherChartWidget(QWidget* parent = nullptr);
	void fresh_display(QList<AppWeatherResult::DailyWeather>& weathers);
	void switch_to_page(const Page& p);
	~WeatherChartWidget();

private:
	using FromDailySession = std::function<int(const AppWeatherResult::DailyWeather&)>;
	void makeup_chart(
		const QList<AppWeatherResult::DailyWeather>& data,
		const QString& title,
		FromDailySession sessionfunc);
	void makeup_mainpage(const QList<AppWeatherResult::DailyWeather>& data);
	Ui::WeatherChartWidget* ui;
};

#endif // WEATHERCHARTWIDGET_H
