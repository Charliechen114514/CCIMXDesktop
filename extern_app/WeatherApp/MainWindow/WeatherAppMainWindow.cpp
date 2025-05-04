#include "WeatherAppMainWindow.h"
#include "AppWeatherRequest.h"
#include "DesktopToast.h"
#include "ui_WeatherAppMainWindow.h"

WeatherAppMainWindow::WeatherAppMainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::WeatherAppMainWindow) {
    ui->setupUi(this);
    setup_internal();
    setup_connections();
    /* post request once */
    refresh_post_request();
}

WeatherAppMainWindow::~WeatherAppMainWindow() {
    delete ui;
}

/* Make the request here */
void WeatherAppMainWindow::refresh_post_request() {
	request->async_request(WEB_URL);
	toast->set_message("Start Depatch Request!");
}

void WeatherAppMainWindow::makeup_errors(QNetworkReply* reply) {
	toast->set_message("Network Error: " + reply->errorString() + ", check your settings");
}

void WeatherAppMainWindow::setup_internal() {
	toast = new DesktopToast(this);
	request = new AppWeatherRequest(this);
	request->bindAppDetailedRequest({ 0, 5, "changchun" });
	result = new AppWeatherResult(this);
}

void WeatherAppMainWindow::setup_connections() {

	connect(ui->actionrefresh, &QAction::triggered,
			this, &WeatherAppMainWindow::refresh_post_request);

	connect(ui->actionexit, &QAction::triggered,
			this, &QApplication::exit);

	connect(request, &AppWeatherRequest::result_available,
			result, &AppWeatherResult::parseJsonString);

	connect(request, &AppWeatherRequest::errorOccurs,
			this, &WeatherAppMainWindow::makeup_errors);

	connect(result, &AppWeatherResult::finish_parse,
			this, &WeatherAppMainWindow::reach_result);
}

void WeatherAppMainWindow::reach_result() {
	toast->set_message("Session success!");
	ui->widget->fresh_display(result->daily_weather);
}
