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
    post_setup_ui();
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

void WeatherAppMainWindow::switch_city() {
	request->bindAppDetailedRequest({ 0, 5, lineEdit->text() });
	refresh_post_request();
}

void WeatherAppMainWindow::setup_internal() {
	toast = new DesktopToast(this);
	request = new AppWeatherRequest(this);
	request->bindAppDetailedRequest({ 0, 5, default_city });
	result = new AppWeatherResult(this);
	lineEdit = new QLineEdit(this);
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

	connect(lineEdit, &QLineEdit::returnPressed, this, &WeatherAppMainWindow::switch_city);
}

void WeatherAppMainWindow::reach_result() {
	toast->set_message("Session success!");
	ui->widget->fresh_display(result->daily_weather);
}

void WeatherAppMainWindow::post_setup_ui() {
	QLabel* display_label = new QLabel(this);
	display_label->setMaximumWidth(150);
	display_label->setText(def_indicate_label_text);
	lineEdit->setMaximumWidth(200);
	lineEdit->setText(default_city);
	ui->toolBar->addWidget(display_label);
	ui->toolBar->addWidget(lineEdit);
}
