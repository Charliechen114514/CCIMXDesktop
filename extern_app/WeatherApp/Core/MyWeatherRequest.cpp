#include "MyWeatherRequest.h"
#include <QNetworkReply>
#include <QUrlQuery>

WeatherRequest::WeatherRequest(QObject* parent)
	: QObject(parent) {
	connect(&manager, &QNetworkAccessManager::finished,
			this, &WeatherRequest::onReplyFinished);
}

void WeatherRequest::async_request(const char* base_url) {
	QUrl url(base_url);
	QUrlQuery special_query = compose_request();
	url.setQuery(special_query);
	QNetworkRequest request(url);
	manager.get(request);
}

void WeatherRequest::onReplyFinished(QNetworkReply* reply) {
	if (reply->error() != QNetworkReply::NoError) {
		emit errorOccurs(reply);
		return; /* repost the issue again */
	}

	QByteArray responseData = reply->readAll();
	QString json(responseData);
	emit result_available(json);

	/* heap reply expected to release */
	reply->deleteLater();
}
