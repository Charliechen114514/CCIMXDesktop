#ifndef MYWEATHERREQUEST_H
#define MYWEATHERREQUEST_H
#include <QNetworkAccessManager>
#include <QtClassHelperMacros>
/*
 * my weather request is the virtual class trying to
 * make a request to the web apps, including some neccesary interfaces
 */
/* This is an abstruct Interfaces */
/* At some cases */
struct WeatherResult : public QObject {
	Q_OBJECT
public:
	explicit WeatherResult(QObject* obj = nullptr)
		: QObject(obj) { }
	virtual void parseJsonString(const QString json) = 0;

signals:
	void finish_parse();
	/* when error occurs */
	void error_occurs(QString cached_error_string);
};

class WeatherRequest : public QObject {
	Q_OBJECT
public:
	Q_DISABLE_COPY(WeatherRequest);
	explicit WeatherRequest(QObject* parent = nullptr);
	/* async compose the request */
	void async_request(const char* base_url);
	/*	interfaces */
	/* expected the redefined request method */
	virtual QUrlQuery compose_request() = 0;

protected:
	/* actually managing the request */
	QNetworkAccessManager manager;
	static constexpr const char* private_key = _DEF_WEATHER_PRIVATE_KEY;

signals:
	/* post this again */
	void errorOccurs(QNetworkReply* reply);
	/* bind the signals for the async fetch */
	void result_available(const QString json);
private slots:
	void onReplyFinished(QNetworkReply* reply);
};

#endif // MYWEATHERREQUEST_H
