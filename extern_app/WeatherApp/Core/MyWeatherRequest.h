#ifndef MYWEATHERREQUEST_H
#define MYWEATHERREQUEST_H

#include <QNetworkAccessManager>
#include <QtClassHelperMacros>

/**
 * @brief The WeatherResult class provides the weather result interfaces.
 *
 * @note WeatherResult is an abstract class that defines how to parse
 * JSON strings retrieved from the web apps.
 */
struct WeatherResult : public QObject {
    Q_OBJECT
public:
    /**
     * @brief Constructor for WeatherResult.
     * @param obj The parent QObject.
     */
    explicit WeatherResult(QObject* obj = nullptr)
        : QObject(obj) { }

    /**
     * @brief Parses the JSON string.
     * @param json The JSON string to parse.
     */
    virtual void parseJsonString(const QString json) = 0;

signals:
    /**
     * @brief Emitted when the parsing is finished.
     */
    void finish_parse();

    /**
     * @brief Emitted when an error occurs.
     * @param cached_error_string The error string.
     */
    void error_occurs(QString cached_error_string);
};

/**
 * @brief The WeatherRequest class provides the interface to request weather data.
 *
 * This class manages the HTTP requests and handles the returned JSON.
 */
class WeatherRequest : public QObject {
    Q_OBJECT
public:
    /**
     * @brief Disables copy constructor and copy assignment.
     * This prevents copying of the WeatherRequest object.
     */
    Q_DISABLE_COPY(WeatherRequest);

    /**
     * @brief Constructor for WeatherRequest.
     * @param parent The parent QObject.
     */
    explicit WeatherRequest(QObject* parent = nullptr);

    /**
     * @brief Sends the request asynchronously.
     * @param base_url The base URL without any request parameters.
     */
    void async_request(const char* base_url);

    /**
     * @brief Composes the request parameters.
     * @return The composed request query.
     */
    virtual QUrlQuery compose_request() = 0;

protected:
    QNetworkAccessManager manager; ///< The network manager handling requests.

    /**
     * @brief Private key for accessing the weather service.
     */
    static constexpr const char* private_key = _DEF_WEATHER_PRIVATE_KEY;

signals:
    /**
     * @brief Emitted when an error occurs in the request.
     * @param reply The reply object that caused the error.
     */
    void errorOccurs(QNetworkReply* reply);

    /**
     * @brief Emitted when the result is available.
     * @param json The JSON string returned from the request.
     */
    void result_available(const QString json);

private slots:
    /**
     * @brief Called when the reply is finished.
     * @param reply The reply object from the request.
     */
    void onReplyFinished(QNetworkReply* reply);
};

#endif // MYWEATHERREQUEST_H
