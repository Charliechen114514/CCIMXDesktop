#ifndef WEATHERAPPMAINWINDOW_H
#define WEATHERAPPMAINWINDOW_H
#include <QMainWindow>
#include <QNetworkReply>
class AppWeatherRequest;
class AppWeatherResult;
class DesktopToast;
class QLineEdit;
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
	static constexpr const char* default_city = "changchun";
	static constexpr const char* def_indicate_label_text = "Current Searching City: ";

public:
	static constexpr const char* WEB_URL = _DEF_WEATHER_URL; ///< request base url
	/**
	 * @brief Construct a new Weather App Main Window object
	 * 
	 * @param parent 
	 */
	WeatherAppMainWindow(QWidget* parent = nullptr);
	/**
	 * @brief Destroy the Weather App Main Window object
	 * 
	 */
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
	/**
	 * @brief switch_city switch the city then
	 */
	void switch_city();

private:
	/**
	 * @brief setup_internal makes the basic init of the
	 * memory issue setups
	 */
	void setup_internal();
	/**
	 * @brief setup_connections really setup the internal connections
	 */
	void setup_connections();
	/**
	 * @brief reach_result is the slot of parse finish, which means
	 * the result is finally available to display from remote!
	 */
	void reach_result();
	void post_setup_ui();
	Ui::WeatherAppMainWindow* ui;
	/* App request and result */
	AppWeatherResult* result;
	AppWeatherRequest* request;
	DesktopToast* toast;
	QLineEdit* lineEdit { nullptr };
};
#endif // WEATHERAPPMAINWINDOW_H
