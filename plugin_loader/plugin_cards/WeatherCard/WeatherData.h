/**
 * @file WeatherData.h
 * @brief Defines data structures for weather information and geographical location.
 */

#ifndef WEATHERDATA_H
#define WEATHERDATA_H

#include <QString> // For QString to hold text data

/**
 * @struct WeatherData
 * @brief Represents a snapshot of weather conditions for a specific location and time.
 *
 * This structure holds various meteorological parameters, including temperature,
 * wind details, and a description of the current weather, along with metadata
 * such as city and observation time.
 */
struct WeatherData {
    QString city; ///< The name of the city for which the weather data is provided.
    QString time; ///< The local time of the weather observation (e.g., "HH:MM AM/PM" or "YYYY-MM-DD HH:MM").
    int interval; ///< The forecast interval in seconds (e.g., 900 for 15 minutes, 3600 for 1 hour).
    double temperature; ///< The temperature in Celsius or Fahrenheit (unit implicitly defined by context).
    double windspeed; ///< The wind speed (unit implicitly defined by context, e.g., m/s, km/h, mph).
    int winddirection; ///< The wind direction in degrees (0-359, where 0 is North, 90 is East, etc.).
    int isDay; ///< Indicates if it's currently daytime (1) or nighttime (0).
    int weatherCode; ///< A numerical code representing the weather condition (e.g., WMO weather codes).
    QString weatherDescription; ///< A textual description of the weather condition (e.g., "Clear sky", "Partly cloudy").
};

/**
 * @struct LocationData
 * @brief Represents geographical coordinates (latitude and longitude).
 *
 * This structure is used to specify a point on the Earth's surface,
 * typically used for identifying the location for which weather data is requested or provided.
 */
struct LocationData {
    double latitude; ///< The latitude coordinate (degrees, typically -90 to +90).
    double longitude; ///< The longitude coordinate (degrees, typically -180 to +180).
};

#endif // WEATHERDATA_H
