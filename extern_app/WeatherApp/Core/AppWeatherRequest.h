#ifndef APPWEATHERREQUEST_H
#define APPWEATHERREQUEST_H
#include "MyWeatherRequest.h"

/**
 * @brief The AppWeatherResult class
 * The AppWeatherResult class provides the weather result
 * and implements the WeatherResult function
 */
class AppWeatherResult : public WeatherResult {
public:
	explicit AppWeatherResult(QObject* parent = nullptr)
		: WeatherResult(parent) { }

	/**
	 * @brief parseJsonString parse the json from remote webs
	 * @param json the json string
	 */
	void parseJsonString(const QString json) override;

	/**
	 * @brief debugPrint print the json object
	 */
	void debugPrint() const;

	/**
	 * @brief The DailyWeather class
	 *	The DailyWeather class provides the daily weather
	 * json strings is expected to serialize into this struct
	 */
	struct DailyWeather {
		QString date; ///< date
		QString textDay; ///< day text
		QString textNight; ///< night text
		QString high; ///< high temperature
		QString low; ///< low temperature
		QString windDirection; ///< wind direction
		QString windScale; ///< wind scale
		QString humidity; ///< humidity
	};
	QString cached_city; ///< city required
	QList<DailyWeather> daily_weather; ///< daily weather
};

/**
 * @brief The AppWeatherDetailedRequest class
 * The AppWeatherDetailedRequest class provides the detailed request
 * for the weather, for example, the start day and the number of days
 * we shell request
 */
struct AppWeatherDetailedRequest {
	unsigned short start;
	unsigned short days;
	QString city;
};

/**
 * @brief The AppWeatherRequest class
 * The AppWeatherRequest class provides the weather request
 * and implements the WeatherRequest function
 */
class AppWeatherRequest : public WeatherRequest {
public:
	Q_DISABLE_COPY(AppWeatherRequest);
	AppWeatherRequest(QObject* parent = nullptr)
		: WeatherRequest(parent) { };

	/**
	 * @brief bindAppDetailedRequest
	 * @param request request we shell make
	 */
	inline void bindAppDetailedRequest(
		const AppWeatherDetailedRequest& request) {
		this->request = request;
	}
	/* add our query issue here */
	QUrlQuery compose_request() override;

private:
	AppWeatherDetailedRequest request;
};

#endif // APPWEATHERREQUEST_H
