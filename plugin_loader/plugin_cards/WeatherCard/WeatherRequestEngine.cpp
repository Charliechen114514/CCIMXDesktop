#include "WeatherRequestEngine.h"
#include "QueryCached.h"
#include <QDebug>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QTimer>
#include <QUrl>
#include <QUrlQuery>
namespace {
QString getWeatherDescription(int weatherCode) {
    switch (weatherCode) {
    case 0:
        return "Clear sky";
    case 1:
        return "Mainly clear";
    case 2:
        return "Partly cloudy";
    case 3:
        return "Overcast";
    case 45:
    case 48:
        return "Fog";
    case 51:
    case 53:
    case 55:
        return "Drizzle";
    case 56:
    case 57:
        return "Freezing drizzle";
    case 61:
    case 63:
    case 65:
        return "Rain";
    case 66:
    case 67:
        return "Freezing rain";
    case 71:
    case 73:
    case 75:
        return "Snow fall";
    case 77:
        return "Snow grains";
    case 80:
    case 81:
    case 82:
        return "Rain showers";
    case 85:
    case 86:
        return "Snow showers";
    case 95:
        return "Thunderstorm";
    case 96:
    case 99:
        return "Thunderstorm with hail";
    default:
        return "Unknown";
    }
}
}

QMap<QString, LocationData> WeatherRequestEngine::s_locationCache;

WeatherRequestEngine::WeatherRequestEngine(const QString& city, QObject* parent)
    : QObject { parent }
    , city_request(city) {
    manager = new QNetworkAccessManager(this);
    cached_weather_data = new QueryCached(this);
    cached_weather_data->setTimeoutInterval(3600 * 1000);
    connect(cached_weather_data, &QueryCached::weatherCacheOutdated,
            this, &WeatherRequestEngine::forceQueryWeatherData);

    if (s_locationCache.contains(city_request.toLower())) {
        currentLocation = s_locationCache.value(city_request.toLower());
        locationFound = true;
        qDebug() << "Location found in cache for " << city_request << ": lat=" << currentLocation.latitude << ", lon=" << currentLocation.longitude;
    }
    timeoutTimer = new QTimer(this);
    timeoutTimer->setSingleShot(true);
}

void WeatherRequestEngine::queryWeatherData() {
    if (city_request.isEmpty()) {
        emit errorOccurred("City name cannot be empty.");
        return;
    }

    std::optional<WeatherData> cachedData = cached_weather_data->requestWeatherData();
    if (cachedData.has_value()) {
        qDebug() << "Returning cached weather data for " << city_request;
        emit weatherDataReady(cachedData.value());
        return;
    }

    if (locationFound) {
        forceQueryWeatherData();
    } else {
        qDebug() << "Fetching location for " << city_request;
        QUrl url("http://nominatim.openstreetmap.org/search");
        QUrlQuery q;
        q.addQueryItem("q", city_request);
        q.addQueryItem("format", "json");
        q.addQueryItem("limit", "1");
        url.setQuery(q);
        qDebug() << "Request URL:" << url.toString();
        QNetworkRequest req(url);
        req.setHeader(QNetworkRequest::UserAgentHeader, "QtWeatherApp/1.0");
        QObject::connect(manager, &QNetworkAccessManager::finished,
                         this, &WeatherRequestEngine::onGeoReply, Qt::SingleShotConnection);
        auto reply = manager->get(req);
        timeoutTimer->start(3000);
        QMetaObject::Connection* timeoutConn = new QMetaObject::Connection;

        *timeoutConn = connect(timeoutTimer, &QTimer::timeout, this,
                               [reply, timeoutConn]() {
                                   if (reply->isRunning()) {
                                       qDebug() << "Request timeout, aborting...";
                                       reply->abort();
                                   }
                                   QObject::disconnect(*timeoutConn);
                                   delete timeoutConn;
                               });
    }
}

void WeatherRequestEngine::forceQueryWeatherData() {
    // 只有在获取到地理位置后才能请求天气
    if (!locationFound) {
        qDebug() << "Cannot force query weather: location not found.";
        emit errorOccurred("Cannot query weather: city location not determined.");
        return;
    }

    qDebug() << "Force querying weather for " << city_request << " (lat:" << currentLocation.latitude << ", lon:" << currentLocation.longitude << ")";
    QUrl url("http://api.open-meteo.com/v1/forecast");
    QUrlQuery q;
    q.addQueryItem("latitude", QString::number(currentLocation.latitude));
    q.addQueryItem("longitude", QString::number(currentLocation.longitude));
    q.addQueryItem("current_weather", "true");
    q.addQueryItem("hourly", "temperature_2m");
    q.addQueryItem("timezone", "Asia/Shanghai");
    url.setQuery(q);
    qDebug() << "Request URL:" << url.toString();

    QNetworkRequest req(url);
    req.setHeader(QNetworkRequest::UserAgentHeader, "QtWeatherApp/1.0");
    QObject::connect(manager, &QNetworkAccessManager::finished,
                     this, &WeatherRequestEngine::onWeatherReply, Qt::SingleShotConnection);
    auto reply = manager->get(req);
    timeoutTimer->start(3000);
    QMetaObject::Connection* timeoutConn = new QMetaObject::Connection;

    *timeoutConn = connect(timeoutTimer, &QTimer::timeout, this,
                          [reply, timeoutConn]() {
        if (reply->isRunning()) {
            qDebug() << "Request timeout, aborting...";
            reply->abort();
        }
        QObject::disconnect(*timeoutConn);
        delete timeoutConn;
    });

}

void WeatherRequestEngine::onGeoReply(QNetworkReply* reply) {
    if (timeoutTimer->isActive())
        timeoutTimer->stop();
    if (reply->error() != QNetworkReply::NoError) {
        QString errorMessage = "Geo API Error: " + reply->errorString();
        qDebug() << errorMessage;
        emit errorOccurred(errorMessage);
        reply->deleteLater();
        qDebug() << "Use default to query!";
        currentLocation.latitude = 38;
        currentLocation.longitude = 121;
    }else{
        auto doc = QJsonDocument::fromJson(reply->readAll());
        reply->deleteLater();

        auto arr = doc.array();
        if (arr.isEmpty()) {
            QString errorMessage = "No geographic information found for " + city_request;
            qDebug() << errorMessage;
            emit errorOccurred(errorMessage);
            return;
        }

        auto obj = arr.first().toObject();
        currentLocation.latitude = obj["lat"].toString().toDouble();
        currentLocation.longitude = obj["lon"].toString().toDouble();

    }

    locationFound = true;

    qDebug() << "Location obtained for " << city_request << ": lat=" << currentLocation.latitude << " lon=" << currentLocation.longitude;
    s_locationCache.insert(city_request.toLower(), currentLocation);
    forceQueryWeatherData();
}

void WeatherRequestEngine::onWeatherReply(QNetworkReply* reply) {
    if (timeoutTimer->isActive())
        timeoutTimer->stop();
    if (reply->error() != QNetworkReply::NoError) {
        QString errorMessage = "Weather API Error: " + reply->errorString();
        qDebug() << errorMessage;
        emit errorOccurred(errorMessage);
        reply->deleteLater();
        return;
    }

    auto doc = QJsonDocument::fromJson(reply->readAll());
    reply->deleteLater();

    auto root = doc.object();

    if (root.contains("current_weather")) {
        auto cw = root["current_weather"].toObject();
        WeatherData weather;
        weather.time = cw["time"].toString();
        weather.interval = cw["interval"].toInt();
        weather.temperature = cw["temperature"].toDouble();
        weather.windspeed = cw["windspeed"].toDouble();
        weather.winddirection = cw["winddirection"].toInt();
        weather.isDay = cw["is_day"].toInt();
        weather.weatherCode = cw["weathercode"].toInt();
        weather.weatherDescription = getWeatherDescription(weather.weatherCode);
        weather.city = city_request;
        // 将新获取的天气数据安装到缓存
        cached_weather_data->installWeatherData(weather);

        auto placeholder = qDebug() << QString(
                                           "Weather for %1:\n"
                                           "Time: %2\n"
                                           "Interval(s): %3\n"
                                           "Temperature: %4 °C\n"
                                           "Wind: %5 km/h @ %6°\n"
                                           "Is Day: %7\n"
                                           "Weather Code: %8 (%9)"
                                           "Weather City for %10:\n")
                                           .arg(city_request)
                                           .arg(weather.time)
                                           .arg(weather.interval)
                                           .arg(weather.temperature)
                                           .arg(weather.windspeed)
                                           .arg(weather.winddirection)
                                           .arg(weather.isDay)
                                           .arg(weather.weatherCode)
                                           .arg(weather.weatherDescription)
                                           .arg(city_request);
        emit weatherDataReady(weather);
    } else {
        QString errorMessage = "Weather data not found in response for " + city_request;
        qDebug() << errorMessage;
        emit errorOccurred(errorMessage);
    }
}
