#include "lightcontrollerwindow.h"
#include "./ui_lightcontrollerwindow.h"

LightControllerWindow::LightControllerWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::LightControllerWindow) {
    ui->setupUi(this);
    init_mode();
    ledController.redirectTo(DEV_FILE);
    plain_package = new LEDParamsPackagePlain(init_state);
    blink = new LEDParamsPackageBlink(BLINK_DEF, BLINK_DEF);
    connect(ui->led_status, &QPushButton::clicked, this, &LightControllerWindow::process_flip);
    connect(ui->led_mode, &QPushButton::clicked, this, &LightControllerWindow::process_mode_switching);
    connect(ui->btn_blink_mode_settings, &QPushButton::clicked, this, &LightControllerWindow::process_speed_switching);
    connect(ui->btn_exit, &QPushButton::clicked, this, &LightControllerWindow::close);
}

LightControllerWindow::~LightControllerWindow() {
	delete plain_package;
	delete blink;
	delete ui;
}

void LightControllerWindow::process_flip() {
	if (ledController.getMode() != Modes::Plain) {
		return;
	}
	plain_package->setIsOn(!plain_package->getIsOn());
	if (plain_package->getIsOn()) {
		ui->led_status->setIcon(QIcon(":/icons/led_on.png"));
	} else {
		ui->led_status->setIcon(QIcon(":/icons/led_off.png"));
	}
	ledController.processByPackage(plain_package);
}

void LightControllerWindow::process_blink() {
	if (ledController.getMode() != Modes::Blink) {
		return;
	}

	ledController.processByPackage(blink);
}

void LightControllerWindow::process_mode_switching() {
	if (ledController.getMode() == Modes::Plain) {
		ledController.setMode(Modes::Blink);
	} else {
		ledController.setMode(Modes::Plain);
	}

	if (ledController.getMode() == Modes::Plain) {
		ui->btn_blink_mode_settings->setEnabled(false);
		ui->led_status->setEnabled(true);
		ui->led_mode->setText("Plain");
		ui->led_mode->setIcon(QIcon(":/icons/manual_control.png"));
	} else {
		ui->btn_blink_mode_settings->setEnabled(true);
		ui->led_status->setEnabled(false);
		ui->led_mode->setText("Blink");
		ui->led_mode->setIcon(QIcon(":/icons/blink_mode.png"));
	}
}

void LightControllerWindow::process_speed_switching() {
	if (ledController.getMode() != Modes::Blink)
		return;

	switch (speed) {
	case Speed::Slow:
		speed = Speed::Normal;
		blink->setOnTime(BLINK_DEF);
		blink->setOffTime(BLINK_DEF);
		ui->btn_blink_mode_settings->setText("Normal Blink");
		break;
	case Speed::Normal:
		speed = Speed::Fast;
		blink->setOnTime(BLINK_DEF / 2);
		blink->setOffTime(BLINK_DEF / 2);
		ui->btn_blink_mode_settings->setText("Fast Blink");
		break;
	case Speed::Fast:
		speed = Speed::Slow;
		blink->setOnTime(BLINK_DEF * 2);
		blink->setOffTime(BLINK_DEF * 2);
		ui->btn_blink_mode_settings->setText("Slow Blink");
		break;
	default:
		return;
	}
	process_blink();
}

void LightControllerWindow::init_mode() {
	ui->btn_blink_mode_settings->setEnabled(false);
	ui->led_status->setEnabled(true);
	ui->led_mode->setText("Plain");
	ui->led_mode->setIcon(QIcon(":/icons/manual_control.png"));
}
