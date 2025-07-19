#ifndef WEATHERREQUESTENGINE_H
#define WEATHERREQUESTENGINE_H
#include "WeatherData.h"
#include <QMap>
#include <QNetworkReply>
#include <QObject>
class QNetworkAccessManager;
class QueryCached;

class WeatherRequestEngine : public QObject {
    Q_OBJECT
public:
    explicit WeatherRequestEngine(const QString& city, QObject* parent = nullptr);
    ~WeatherRequestEngine() = default;
    void queryWeatherData();

signals:
    void weatherDataReady(const WeatherData& data);
    void errorOccurred(const QString& errorMessage);

private slots:
    void onGeoReply(QNetworkReply* reply);
    void onWeatherReply(QNetworkReply* reply);
    void forceQueryWeatherData();

private:
    QNetworkAccessManager* manager;
    QString city_request;
    QueryCached* cached_weather_data;
    static QMap<QString, LocationData> s_locationCache;
    LocationData currentLocation;
    bool locationFound { false };
};

#endif // WEATHERREQUESTENGINE_H
