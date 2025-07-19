#include "WeatherCard.h"
#include "WeatherRequestEngine.h"
#include "ui_WeatherCard.h"
#include <QDateTime>
#include <QDebug>
#include <QLabel>
#include <QPixmap>
namespace {
QString getImagePath(int weatherCode, bool isDay) {
    QString path = ":/icons/sources/";

    switch (weatherCode) {
    case 0: // Clear sky
        path += (isDay ? "sunny.png" : "clear.png");
        break;
    case 1: // Mainly clear
    case 2: // Partly cloudy
        path += (isDay ? "partly_cloudy_day.png" : "partly_cloudy_night.png");
        break;
    case 3: // Overcast
        path += (isDay ? "cloudy_day.png" : "cloudy_night");
        break;
    case 45: // Fog
    case 48: // Depositing fog
        path += "fog.png";
        break;
    case 51: // Drizzle: Light
    case 53: // Drizzle: Moderate
    case 55: // Drizzle: Dense intensity
        path += "drizzle.png";
        break;
    case 56: // Freezing Drizzle: Light
    case 57: // Freezing Drizzle: Dense intensity
        path += "freezing_drizzle.png";
        break;
    case 61: // Rain: Light
    case 63: // Rain: Moderate
    case 65: // Rain: Heavy intensity
        path += "rain.png";
        break;
    case 66: // Freezing Rain: Light
    case 67: // Freezing Rain: Heavy intensity
        path += "freezing_rain.png";
        break;
    case 71: // Snow fall: Light
    case 73: // Snow fall: Moderate
    case 75: // Snow fall: Heavy intensity
        path += "snow.png";
        break;
    case 77: // Snow grains
        path += "snow_grains.png";
        break;
    case 80: // Rain showers: Light
    case 81: // Rain showers: Moderate
    case 82: // Rain showers: Violent
        path += "rain_showers.png";
        break;
    case 85: // Snow showers: Light
    case 86: // Snow showers: Heavy
        path += "snow_showers.png";
        break;
    case 95: // Thunderstorm: Light or moderate
        path += "thunderstorm.png";
        break;
    case 96: // Thunderstorm with slight hail
    case 99: // Thunderstorm with heavy hail
        path += "thunderstorm_hail.png";
        break;
    default:
        path += "unknown.png";
        break;
    }
    return path;
}

QString describeTemperature(float tempCelsius) {
    if (tempCelsius < 5)
        return " (Cold)";
    else if (tempCelsius < 15)
        return " (Cool)";
    else if (tempCelsius < 25)
        return " (Comfortable)";
    else if (tempCelsius < 30)
        return " (Warm)";
    else
        return " (Hot)";
}

QString describeWindSpeed(float speedKmh) {
    if (speedKmh < 1)
        return " (Calm)";
    else if (speedKmh < 5)
        return " (Light air)";
    else if (speedKmh < 20)
        return " (Breezy)";
    else if (speedKmh < 40)
        return " (Windy)";
    else if (speedKmh < 60)
        return " (Strong wind)";
    else
        return " (Stormy)";
}

QString describeWindDirection(int degree) {
    static const char* directions[] = {
        "North", "North-Northeast", "Northeast", "East-Northeast",
        "East", "East-Southeast", "Southeast", "South-Southeast",
        "South", "South-Southwest", "Southwest", "West-Southwest",
        "West", "West-Northwest", "Northwest", "North-Northwest"
    };
    int index = static_cast<int>((degree + 11.25) / 22.5) % 16;
    return QString(" (%1)").arg(directions[index]);
}

}

WeatherCard::WeatherCard(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::WeatherCard) {
    ui->setupUi(this);
    engine = new WeatherRequestEngine("dalian", this);
    engine->queryWeatherData();
    connect(engine, &WeatherRequestEngine::weatherDataReady,
            this, &WeatherCard::receiveDatas);
    setObjectName("WeatherCard");
    setAttribute(Qt::WA_StyledBackground);
    setStyleSheet(R"(
    #WeatherCard {
        border-radius: 20px;
        background: qlineargradient(
            x1: 0, y1: 0, x2: 0, y2: 1,
            stop: 0 #87CEFA,
            stop: 1 #00BFFF
        );
    }
    QLabel {
        color: white;
    }
    )");
    ui->descriptionLabel->setStyleSheet("font-size: 48px; font-weight: bold;");
    ui->temperatureLabel->setStyleSheet("font-size: 32px;");
    ui->city_label->setStyleSheet("font-size: 48px;");
    ui->timeLabel->setStyleSheet("font-size: 20px;");
    ui->windSpeedLabel->setStyleSheet("font-size: 20px;");
    ui->windDirectionLabel->setStyleSheet("font-size: 20px;");
}

WeatherCard::~WeatherCard() {
    delete ui;
}

void WeatherCard::receiveDatas(const WeatherData& data) {
    qDebug() << "WeatherCard received data for display.";
    QString imagePath = getImagePath(data.weatherCode, data.isDay);
    QPixmap pixmap(imagePath);
    if (!pixmap.isNull()) {
        ui->weatherIconLabel->setPixmap(pixmap.scaled(ui->weatherIconLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    } else {
        qWarning() << "Failed to load weather icon:" << imagePath;
        ui->weatherIconLabel->setText("No Icon");
    }
    ui->city_label->setText("City: " + data.city);
    ui->descriptionLabel->setText(data.weatherDescription);
    ui->temperatureLabel->setText(
        QString("%1 °C%2").arg(data.temperature, 0, 'f', 1).arg(describeTemperature(data.temperature)));

    QDateTime dateTime = QDateTime::fromString(data.time, Qt::ISODate);
    ui->timeLabel->setText(QString("Query Time: %1").arg(dateTime.toString("hh:mm")));

    ui->windSpeedLabel->setText(
        QString("Speed: %1 km/h%2").arg(data.windspeed, 0, 'f', 1).arg(describeWindSpeed(data.windspeed)));

    ui->windDirectionLabel->setText(
        QString("Direction: %1°%2").arg(data.winddirection).arg(describeWindDirection(data.winddirection)));
}
