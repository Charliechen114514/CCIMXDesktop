#ifndef WEATHERAPPMAINWINDOW_H
#define WEATHERAPPMAINWINDOW_H
#include <QMainWindow>
#include <QNetworkReply>
class AppWeatherRequest;
class AppWeatherResult;
class DesktopToast;
QT_BEGIN_NAMESPACE
namespace Ui {
class WeatherAppMainWindow;
}
QT_END_NAMESPACE

/**
 * @brief The WeatherAppMainWindow class
 * The WeatherAppMainWindow class provides the weather app main window
 */
class WeatherAppMainWindow : public QMainWindow {
	Q_OBJECT

public:
	static constexpr const char* WEB_URL = _DEF_WEATHER_URL;
	WeatherAppMainWindow(QWidget* parent = nullptr);
	~WeatherAppMainWindow();

	/**
	 * @brief refresh_post_request
	 * This function is used to refresh the post request
	 */
	void refresh_post_request();

private slots:
	/**
	 * @brief makeup_errors make up the error from the reply
	 * @param reply
	 */
	void makeup_errors(QNetworkReply* reply);

private:
	void setup_internal();
	void setup_connections();
	void reach_result();
	Ui::WeatherAppMainWindow* ui;
	/* App request and result */
	AppWeatherResult* result;
	AppWeatherRequest* request;
	DesktopToast* toast;
};
#endif // WEATHERAPPMAINWINDOW_H
