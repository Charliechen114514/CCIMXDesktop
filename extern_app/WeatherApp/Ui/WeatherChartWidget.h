#ifndef WEATHERCHARTWIDGET_H
#define WEATHERCHARTWIDGET_H

#include "AppWeatherRequest.h"
#include <QWidget>
#include <QtCharts>
namespace Ui {
class WeatherChartWidget;
}

/**
 * @brief The WeatherChartWidget class provides the weather chart widget
 * @note this is the main page of the weather mainWindows
 * @see WeatherAppMainWindow
 */
class WeatherChartWidget : public QWidget {
	Q_OBJECT

public:
	/**
	 * @brief The Page enum
	 * The Page enum provides the page index
	 * @see switch_to_page to get to know where to use this
	 */
	enum Page {
		MAIN_PAGE, ///< main page
		HIGH_TEMP, ///< high temperature page
		LOW_TEMP, ///< low temperature page
		WINDSCALE, ///< wind scale page
		HUMIDITY ///< humidity page
	};

	explicit WeatherChartWidget(QWidget* parent = nullptr);

	/**
	 * @brief fresh_display
	 * @param weathers
	 * This function is used to refresh the display
	 */
	void fresh_display(QList<AppWeatherResult::DailyWeather>& weathers);

	/**
	 * @brief switch_to_page
	 * @details switch the page to the specified page
	 * @param p the page to be switched
	 */
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
