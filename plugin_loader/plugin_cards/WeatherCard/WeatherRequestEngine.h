/**
 * @file WeatherRequestEngine.h
 * @brief Defines the WeatherRequestEngine class for fetching and managing weather data.
 */

#ifndef WEATHERREQUESTENGINE_H
#define WEATHERREQUESTENGINE_H

#include "WeatherData.h" // Includes WeatherData and LocationData structs
#include <QMap> // For QMap to store location cache
#include <QNetworkReply> // For QNetworkReply to handle network responses
#include <QObject> // Base class for WeatherRequestEngine, enabling signals/slots
#include <QTimer> // Timer
// Forward declarations to avoid heavy includes and circular dependencies
class QNetworkAccessManager;
class QueryCached;

/**
 * @class WeatherRequestEngine
 * @brief Handles the logic for requesting geographical and weather data from network services.
 *
 * This class is responsible for making network requests to obtain location data
 * (latitude and longitude) for a given city, and then using those coordinates
 * to fetch current weather conditions. It utilizes a caching mechanism (`QueryCached`)
 * to reduce redundant API calls and optimize performance. Signals are emitted
 * upon successful data retrieval or if an error occurs.
 */
class WeatherRequestEngine : public QObject {
Q_OBJECT // Enables Qt's meta-object system features like signals and slots

    public :
    /**
     * @brief Constructs a WeatherRequestEngine object.
     * @param city The name of the city for which weather data will be requested.
     * @param parent A pointer to the parent QObject, allowing for proper object hierarchy and memory management. Defaults to nullptr.
     */
    explicit WeatherRequestEngine(const QString& city, QObject* parent = nullptr);

    /**
     * @brief Destroys the WeatherRequestEngine object.
     * 	 * The default destructor is sufficient as `QObject` handles child deletion,
     * and `QueryCached` is a child of this object.
     */
    ~WeatherRequestEngine() = default;

    /**
     * @brief Initiates a request for weather data.
     * 	 * This method first checks the cache. If the cached data is valid, it emits
     * `weatherDataReady` immediately. Otherwise, it triggers network requests:
     * first for geographical coordinates if not already known, then for weather data.
     */
    void queryWeatherData();

signals:
    /**
     * @brief Signal emitted when new weather data is successfully retrieved and ready.
     * @param data A constant reference to the `WeatherData` object containing the fetched weather details.
     */
    void weatherDataReady(const WeatherData data);

    /**
     * @brief Signal emitted when an error occurs during the data request process.
     * @param errorMessage A QString describing the nature of the error.
     */
    void errorOccurred(const QString& errorMessage);

private slots:
    /**
     * @brief Slot to handle the network reply for geographical coordinate requests.
     * 	 * This slot parses the response from a geolocation service. If successful, it
     * extracts the latitude and longitude, updates `currentLocation`, sets `locationFound`
     * to true, and then proceeds to request weather data. Handles network errors.
     * @param reply A pointer to the `QNetworkReply` object for the geolocation request.
     */
    void onGeoReply(QNetworkReply* reply);

    /**
     * @brief Slot to handle the network reply for weather data requests.
     * 	 * This slot parses the response from a weather API. If successful, it
     * extracts weather information, constructs a `WeatherData` object, caches it,
     * and emits the `weatherDataReady` signal. Handles network errors.
     * @param reply A pointer to the `QNetworkReply` object for the weather data request.
     */
    void onWeatherReply(QNetworkReply* reply);

    /**
     * @brief Forces an immediate network request for weather data, bypassing the cache.
     * 	 * This slot is typically connected to `QueryCached::weatherCacheOutdated` to
     * ensure fresh data is fetched when the cached data expires.
     */
    void forceQueryWeatherData();

private:
    QNetworkAccessManager* manager; ///< Manages network requests (e.g., HTTP GET).
    QString city_request; ///< The name of the city for which weather is requested.
    QueryCached* cached_weather_data; ///< Manages caching of `WeatherData` to reduce API calls.
    QTimer* timeoutTimer; ///< timeout timer
    /**
     * @brief A static QMap to cache geographical coordinates for cities.
     * 	 * This static member allows location data for frequently requested cities
     * to be reused across different `WeatherRequestEngine` instances, avoiding
     * redundant geolocation API calls.
     */
    static QMap<QString, LocationData> s_locationCache;

    LocationData currentLocation; ///< Stores the latitude and longitude for the requested city.
    bool locationFound { false }; ///< Flag indicating if the geographical location for `city_request` has been successfully determined.
};

#endif // WEATHERREQUESTENGINE_H
