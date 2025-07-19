#ifndef WEATHERDATA_H
#define WEATHERDATA_H
#include <QString>
struct WeatherData {
    QString city;
    QString time;
    int interval;
    double temperature;
    double windspeed;
    int winddirection;
    int isDay;
    int weatherCode;
    QString weatherDescription;
};

struct LocationData {
    double latitude;
    double longitude;
};
#endif // WEATHERDATA_H
