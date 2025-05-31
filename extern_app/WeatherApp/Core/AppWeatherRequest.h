#ifndef APPWEATHERREQUEST_H
#define APPWEATHERREQUEST_H

#include "MyWeatherRequest.h"

/**
 * @brief The AppWeatherResult class provides the weather result and implements the WeatherResult functionality.
 */
class AppWeatherResult : public WeatherResult {
public:
    /**
     * @brief Constructor for AppWeatherResult.
     * @param parent The parent QObject.
     */
    explicit AppWeatherResult(QObject* parent = nullptr)
        : WeatherResult(parent) { }

    /**
     * @brief Parses the JSON string from remote servers.
     * @param json The JSON string to parse.
     */
    void parseJsonString(const QString json) override;

    /**
     * @brief Prints the parsed JSON object for debugging.
     */
    void debugPrint() const;

    /**
     * @brief The DailyWeather struct provides the daily weather details.
     * The JSON strings are expected to serialize into this struct.
     */
    struct DailyWeather {
        QString date; ///< The date.
        QString textDay; ///< Daytime weather description.
        QString textNight; ///< Nighttime weather description.
        QString high; ///< High temperature.
        QString low; ///< Low temperature.
        QString windDirection; ///< Wind direction.
        QString windScale; ///< Wind scale.
        QString humidity; ///< Humidity percentage.
    };

    QString cached_city; ///< The city for which weather data is requested.
    QList<DailyWeather> daily_weather; ///< The list of daily weather data.
};

/**
 * @brief The AppWeatherDetailedRequest struct provides the detailed request information
 * for the weather, such as the start day and the number of days to request.
 */
struct AppWeatherDetailedRequest {
    unsigned short start; ///< The start day offset.
    unsigned short days; ///< The number of days to request.
    QString city; ///< The city name.
};

/**
 * @brief The AppWeatherRequest class provides the weather request and implements the WeatherRequest functionality.
 */
class AppWeatherRequest : public WeatherRequest {
public:
    /**
     * @brief Disables copy constructor and copy assignment.
     * This prevents copying of the AppWeatherRequest object.
     */
    Q_DISABLE_COPY(AppWeatherRequest);

    /**
     * @brief Constructor for AppWeatherRequest.
     * @param parent The parent QObject.
     */
    AppWeatherRequest(QObject* parent = nullptr)
        : WeatherRequest(parent) { }

    /**
     * @brief Binds a detailed request.
     * @param request The AppWeatherDetailedRequest structure to bind.
     */
    inline void bindAppDetailedRequest(const AppWeatherDetailedRequest& request) {
        this->request = request;
    }

    /**
     * @brief Composes the URL query for the weather request.
     * @return The composed QUrlQuery.
     */
    QUrlQuery compose_request() override;

private:
    AppWeatherDetailedRequest request; ///< The detailed weather request information.
};

#endif // APPWEATHERREQUEST_H
