#ifndef WEATHERDAILYCARD_H
#define WEATHERDAILYCARD_H
#include "AppWeatherRequest.h"
#include <QWidget>
namespace Ui {
class WeatherDailyCard;
}

class WeatherDailyCard : public QWidget {
	Q_OBJECT

public:
	explicit WeatherDailyCard(QWidget* parent = nullptr);
	void bind_daily_info(const AppWeatherResult::DailyWeather& weather);
	~WeatherDailyCard();

private:
	void iconPolicy(const QString& str);
	Ui::WeatherDailyCard* ui;
};

#endif // WEATHERDAILYCARD_H
