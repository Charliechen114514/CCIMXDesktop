#include "WeatherDailyCard.h"
#include "ui_WeatherDailyCard.h"

WeatherDailyCard::WeatherDailyCard(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::WeatherDailyCard) {
	ui->setupUi(this);
	ui->label_icons->setScaledContents(true);
}

void WeatherDailyCard::
	bind_daily_info(const AppWeatherResult::DailyWeather& weather) {

	ui->label_date->setText(weather.date);
	iconPolicy(weather.textDay);
	ui->label_humi->setText("湿度: " + weather.humidity);
	ui->label_temp->setText(QString("温度: %1 - %2").arg(weather.low).arg(weather.high));
	ui->label_winds->setText(QString("风速: %1 风向: %2").arg(weather.windScale).arg(weather.windDirection));
}

WeatherDailyCard::~WeatherDailyCard() {
	delete ui;
}

void WeatherDailyCard::iconPolicy(const QString& str) {
	QPixmap pixmap;
	if (str.contains("晴")) {
		pixmap = QPixmap(":/icons/sunny.png");
	} else if (str.contains("雨")) {
		pixmap = QPixmap(":/icons/rainy.png");
	} else if (str.contains("雪")) {
		pixmap = QPixmap(":/icons/snowy.png");
	} else {
		pixmap = QPixmap(":/icons/cloudy.png");
	}
	ui->label_icons->setPixmap(pixmap.scaled(ui->label_icons->size(), Qt::KeepAspectRatio));
}
