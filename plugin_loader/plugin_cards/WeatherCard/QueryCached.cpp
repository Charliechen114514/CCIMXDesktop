#include "QueryCached.h"
#include <QDebug>
#include <QTimer>
QueryCached::QueryCached(QObject* parent)
    : QObject(parent) {
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &QueryCached::onCacheTimeout);
}

void QueryCached::setTimeoutInterval(int interval) {
    if (interval == -1) {
        timer->stop();
    } else {
        timer->setInterval(interval);
    }
}

void QueryCached::installWeatherData(const WeatherData& data) {
    this->cachedWeatherData = data;
    weatherCacheNeedsUpdate = false;
    timer->start();
}

std::optional<WeatherData> QueryCached::requestWeatherData() {
    if (!weatherCacheNeedsUpdate) {
        return { cachedWeatherData };
    } else {
        emit weatherCacheOutdated();
        return std::nullopt;
    }
}

void QueryCached::onCacheTimeout() {
    weatherCacheNeedsUpdate = true;
    qDebug() << "Weather cache timed out.";
    emit weatherCacheOutdated();
}
