#include "environmentwindow.h"
#include "./ui_environmentwindow.h"
#include <QTimer>
EnvironmentWindow::EnvironmentWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::EnvironmentWindow) {
    ui->setupUi(this);
    setup_memory();
    setup_ui();
}

EnvironmentWindow::~EnvironmentWindow() {
    delete ui;
}

void EnvironmentWindow::setup_memory() {
	period_request_timer = new QTimer(this);
	connect(period_request_timer, &QTimer::timeout, this, [this]() {
		factory.request_data();
	});
	connect(&factory, &AP3216CAdapterFactory::request_finish,
			this, &EnvironmentWindow::process_data);
	period_request_timer->start(1000); // 1 second interval
}

void EnvironmentWindow::setup_ui() {
	// Set up the UI elements here
	ui->AUXGauge->setRange(MIN_ALS_VALUE, MAX_ALS_VALUE);
	ui->PSGauge->setRange(MIN_PS_VALUE, MAX_PS_VALUE);
	ui->IRGauge->setRange(MIN_IR_VALUE, MAX_IR_VALUE);
	ui->AUXGauge->setTitle("ALS");
	ui->AUXGauge->setUnit("");
	ui->PSGauge->setTitle("PS");
	ui->PSGauge->setUnit("");
	ui->IRGauge->setTitle("IR");
	ui->IRGauge->setUnit("");

	connect(ui->actionexit, &QAction::triggered, this, &EnvironmentWindow::close);
	connect(ui->actionrefresh, &QAction::triggered, this, [this]() {
		auto possible_data = factory.sync_request_data();
		if (possible_data.has_value()) {
			process_data(possible_data.value());
		} else {
			qDebug() << "Failed to get data";
		}
	});
	connect(ui->btn_refresh_manual, &QPushButton::clicked, this, [this]() {
		auto possible_data = factory.sync_request_data();
		if (possible_data.has_value()) {
			process_data(possible_data.value());
		} else {
			qDebug() << "Failed to get data";
		}
	});
}

void EnvironmentWindow::process_data(const AP3216CData data) {
	qDebug() << "Received Data: "
			 << "ALS:" << data.als
			 << "PS:" << data.ps
			 << "IR:" << data.ir;
	ui->AUXGauge->update_value(data.als);
	ui->PSGauge->update_value(data.ps);
	ui->IRGauge->update_value(data.ir);
}
