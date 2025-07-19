#ifndef QUERYCACHED_H
#define QUERYCACHED_H

#include "WeatherData.h"
#include <QObject>

class QueryCached : public QObject {
    Q_OBJECT
public:
    explicit QueryCached(QObject* parent = nullptr);
    void setTimeoutInterval(int interval);
    void installWeatherData(const WeatherData& data);
    std::optional<WeatherData> requestWeatherData();

signals:
    void weatherCacheOutdated();

private slots:
    void onCacheTimeout();

private:
    WeatherData cachedWeatherData;
    QTimer* timer;
    bool weatherCacheNeedsUpdate { true };
};

#endif // QUERYCACHED_H
