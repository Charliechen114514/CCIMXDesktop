/**
 * @file QueryCached.h
 * @brief Defines the QueryCached class, a utility for managing cached data with a timeout mechanism.
 */

#ifndef QUERYCACHED_H
#define QUERYCACHED_H

#include "WeatherData.h" // Assumed to be a struct or class containing weather information
#include <QObject> // Base class for QueryCached, enabling signals/slots
#include <optional> // For std::optional in requestWeatherData

// Forward declaration
class QTimer; // Required for the timer member

/**
 * @class QueryCached
 * @brief Manages a cache of `WeatherData` with an automatic timeout mechanism.
 *
 * This class provides a simple caching mechanism for `WeatherData`. It allows
 * storing data and retrieving it, but the cached data becomes "outdated" after
 * a specified timeout interval. When the cache is outdated, it indicates that
 * fresh data should be fetched. It uses a `QTimer` to manage the timeout.
 */
class QueryCached : public QObject {
    Q_OBJECT

public:
    /**
     * @brief Constructs a QueryCached object.
     * @param parent A pointer to the parent QObject, allowing for proper object hierarchy and memory management. Defaults to nullptr.
     */
    explicit QueryCached(QObject* parent = nullptr);

    /**
     * @brief Sets the timeout interval for the cached data.
     * 	 * After this interval (in milliseconds) passes since the last `installWeatherData` call,
     * the cached data will be considered outdated.
     * @param interval The timeout interval in milliseconds.
     */
    void setTimeoutInterval(int interval);

    /**
     * @brief Installs new `WeatherData` into the cache.
     * 	 * When new data is installed, the cache is marked as fresh, and the timeout timer is restarted.
     * @param data A constant reference to the `WeatherData` to be cached.
     */
    void installWeatherData(const WeatherData& data);

    /**
     * @brief Requests the cached `WeatherData`.
     * 	 * If the cached data is valid and not outdated, it is returned. If the cache is
     * outdated, `std::nullopt` is returned, and the `weatherCacheOutdated` signal is emitted.
     * @return An `std::optional<WeatherData>` containing the cached data if valid, otherwise `std::nullopt`.
     */
    std::optional<WeatherData> requestWeatherData();

signals:
    /**
     * @brief Signal emitted when the cached weather data becomes outdated.
     * 	 * This signal indicates that a fresh fetch of weather data is required.
     */
    void weatherCacheOutdated();

private slots:
    /**
     * @brief Slot triggered when the cache timeout timer expires.
     * 	 * This slot marks the cached data as outdated and emits the `weatherCacheOutdated` signal.
     */
    void onCacheTimeout();

private:
    WeatherData cachedWeatherData; ///< The actual `WeatherData` stored in the cache.
    QTimer* timer; ///< A QTimer to manage the cache timeout.
    bool weatherCacheNeedsUpdate { true }; ///< A flag indicating whether the cached data is outdated and needs updating.
};

#endif // QUERYCACHED_H
