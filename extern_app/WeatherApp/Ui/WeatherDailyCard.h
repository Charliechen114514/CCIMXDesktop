#ifndef WEATHERDAILYCARD_H
#define WEATHERDAILYCARD_H
#include "AppWeatherRequest.h"
#include <QWidget>
namespace Ui {
class WeatherDailyCard;
}

/**
 * @brief The WeatherDailyCard class provides the daily weather card
 * @note this is used to display the daily weather
 */
class WeatherDailyCard : public QWidget {
	Q_OBJECT

public:
	/**
	 * @brief The WeatherDailyCard class provides the daily weather card
	 * @note this is used to display the daily weather
	 */
	explicit WeatherDailyCard(QWidget* parent = nullptr);

	/**
	 * @brief bind_daily_info
	 * @param weather the weather to be displayed
	 * @note this function is used to bind the daily weather info
	 */
	void bind_daily_info(const AppWeatherResult::DailyWeather& weather);
	~WeatherDailyCard();

private:
	void iconPolicy(const QString& str);
	Ui::WeatherDailyCard* ui;
};

#endif // WEATHERDAILYCARD_H
