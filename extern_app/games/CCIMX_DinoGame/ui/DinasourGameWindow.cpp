#include "DinasourGameWindow.h"
#include "ui_DinasourGameWindow.h"
#include <QMessageBox>
#include <QPushButton>
DinasourGameWindow::DinasourGameWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::DinasourGameWindow) {
	ui->setupUi(this);
	setup_my_ui();
	setup_connections();
}

DinasourGameWindow::~DinasourGameWindow() {
	delete ui;
}

void DinasourGameWindow::process_gameend() {
	ui->actionPause->setEnabled(false);
	auto infoPack = ui->main_widget->infoPack();

	QMessageBox::information(
		this, "You Died!",
		QString("You have gained: %1 scores\nWith Difficulty: " + dif_str_fac(infoPack.t)).arg(infoPack.score));

	if (QMessageBox::Yes == QMessageBox::question(this, "Restart?", "Wanna try again?")) {
		ui->main_widget->clearAndReset();
	} else {
		close();
	}
}

void DinasourGameWindow::post_game_start() {
	make_pause = false;
	ui->actionPause->setText("Pause");
	ui->actionPause->setEnabled(true);
}

void DinasourGameWindow::setup_connections() {
	connect(ui->actionexit, &QAction::triggered,
			ui->main_widget, &DinasourGameMainWidget::process_die);

	connect(ui->actionPause, &QAction::triggered, this, [this]() {
		make_pause = !make_pause;
		if (make_pause) {
			ui->main_widget->pause();
			ui->actionPause->setText("Resume");
		} else {
			ui->main_widget->resume();
			ui->actionPause->setText("Pause");
		}
	});

	connect(ui->main_widget, &DinasourGameMainWidget::game_overed,
			this, &DinasourGameWindow::process_gameend);
	connect(ui->main_widget, &DinasourGameMainWidget::game_started,
			this, &DinasourGameWindow::post_game_start);

	connect(layup_btn, &QPushButton::pressed, ui->main_widget, &DinasourGameMainWidget::animate_lay);
	connect(layup_btn, &QPushButton::released, this, [this]() {
		ui->main_widget->setFocus();
		ui->main_widget->animate_up();
	});
}

void DinasourGameWindow::setup_my_ui() {
	ui->actionPause->setEnabled(false);
	layup_btn = new QPushButton(this);
	layup_btn->setText("Duckling!");
	layup_btn->setMinimumHeight(40);
	ui->toolBar->addSeparator();
	ui->toolBar->addWidget(layup_btn);
}
