#include "AppWeatherRequest.h"
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QUrlQuery>
/*
 *  ToDo: Make A Better Request
 */
QUrlQuery AppWeatherRequest::compose_request() {
	QUrlQuery query;
	query.addQueryItem("key", _DEF_WEATHER_PRIVATE_KEY);
	query.addQueryItem("location", request.city);
	query.addQueryItem("language", "zh-Hans");
	query.addQueryItem("unit", "c");
	query.addQueryItem("start", QString::number(request.start));
	query.addQueryItem("days", QString::number(request.days));
	return query;
}

void AppWeatherResult::parseJsonString(const QString json) {
	QJsonParseError error;
	QJsonDocument doc = QJsonDocument::fromJson(json.toUtf8(), &error);

	if (error.error != QJsonParseError::NoError) {
		emit error_occurs(error.errorString());
		return;
	}

	QJsonObject root = doc.object();
	QJsonArray results = root.value("results").toArray();
	if (results.isEmpty()) {
		emit error_occurs("Result is Empty, debug the sessions!");
		return;
	}

	QJsonObject result = results.at(0).toObject();
	QJsonObject location = result.value("location").toObject();
	cached_city = location.value("name").toString();
	daily_weather.clear();
	QJsonArray daily = result.value("daily").toArray();
	for (const QJsonValueConstRef& v : std::as_const(daily)) {
		QJsonObject obj = v.toObject();
		DailyWeather weather;
		weather.date = obj.value("date").toString();
		weather.textDay = obj.value("text_day").toString();
		weather.textNight = obj.value("text_night").toString();
		weather.high = obj.value("high").toString();
		weather.low = obj.value("low").toString();
		weather.windDirection = obj.value("wind_direction").toString();
		weather.windScale = obj.value("wind_scale").toString();
		weather.humidity = obj.value("humidity").toString();
		daily_weather.push_back(weather);
	}
	emit finish_parse();
}

void AppWeatherResult::debugPrint() const {
	qDebug() << "城市:" << cached_city;
	for (const DailyWeather& weather : daily_weather) {
		qDebug() << "日期:" << weather.date
				 << "白天:" << weather.textDay
				 << "夜间:" << weather.textNight
				 << "温度:" << weather.low << "~" << weather.high << "℃"
				 << "风向:" << weather.windDirection
				 << "风力:" << weather.windScale
				 << "湿度:" << weather.humidity << "%";
	}
}
