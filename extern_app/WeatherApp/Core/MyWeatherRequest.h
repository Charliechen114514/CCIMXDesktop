#ifndef MYWEATHERREQUEST_H
#define MYWEATHERREQUEST_H
#include <QNetworkAccessManager>
#include <QtClassHelperMacros>

/**
 * @brief The WeatherResult class
 * The WeatherResult class provides the weather result interfaces
 * @notes my weather request is the virtual class trying to
 * make a request to the web apps, including some neccesary interfaces
 */
struct WeatherResult : public QObject {
	Q_OBJECT
public:
	explicit WeatherResult(QObject* obj = nullptr)
		: QObject(obj) { }
	/**
	 * @brief parseJsonString defines how to parse json strings
	 * @param json the json string waiting parse
	 */
	virtual void parseJsonString(const QString json) = 0;

signals:
	/**
	 * @brief finish_parse
	 * when the parsing is finished, this signal will be emitted
	 */
	void finish_parse();

	/**
	 * @brief error_occurs
	 * when an error occurs, this signal will be emitted
	 * @param cached_error_string the error string
	 */
	void error_occurs(QString cached_error_string);
};

class WeatherRequest : public QObject {
	Q_OBJECT
public:
	Q_DISABLE_COPY(WeatherRequest);
	explicit WeatherRequest(QObject* parent = nullptr);

	/**
	 * @brief async_request
	 * this function is used to send the request
	 * @param base_url, the url without any request sessions
	 * only the base url is provided
	 */
	void async_request(const char* base_url);
	/*	interfaces */

	/**
	 * @brief compose_request
	 * compose request required devs to complete the
	 * function of how to compose the request
	 * @return the request url
	 */
	virtual QUrlQuery compose_request() = 0;

protected:
	/* actually managing the request */
	QNetworkAccessManager manager;
	static constexpr const char* private_key = _DEF_WEATHER_PRIVATE_KEY;

signals:
	/**
	 * @brief errorOccurs
	 * when an error occurs, this signal will be emitted
	 * @param reply
	 * the reply from the request
	 */
	void errorOccurs(QNetworkReply* reply);

	/**
	 * @brief result_available
	 * when the result is available, this signal will be emitted
	 * @param json
	 * the json string from the request
	 */
	void result_available(const QString json);
private slots:
	/**
	 * @brief onReplyFinished
	 * when the reply is finished, this slot will be called
	 * @param reply the reply from the request
	 */
	void onReplyFinished(QNetworkReply* reply);
};

#endif // MYWEATHERREQUEST_H
