#include "EasyNoteMainWindow.h"
#include "LeftSideBar.h"
#include "MainSideBar.h"
#include "ui_EasyNoteMainWindow.h"
EasyNoteMainWindow::EasyNoteMainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::EasyNoteMainWindow) {
	ui->setupUi(this);
	left = new LeftSideBar(this);
	mainSideBar = new MainSideBar(this);
	mainSideBar->bind_sidebar(left);
	ui->centralwidget->addLayout({ left }, SideBarWidget::Role::SideBar);
	ui->centralwidget->addLayout({ mainSideBar }, SideBarWidget::Role::MainSide);
	init_connections();
}

EasyNoteMainWindow::~EasyNoteMainWindow() {
	delete ui;
}

void EasyNoteMainWindow::init_connections() {
	connect(left, &LeftSideBar::load_file, mainSideBar, &MainSideBar::commit_file);
	connect(left, &LeftSideBar::load_temp, mainSideBar, &MainSideBar::display_temperary);
	connect(mainSideBar, &MainSideBar::submit_enhist_request, left, &LeftSideBar::enqueue_history_file);
	connect(ui->actiontoolbars, &QAction::triggered, ui->centralwidget, &SideBarWidget::switch_state);
	connect(ui->actionexit, &QAction::triggered, this, &EasyNoteMainWindow::close);
	connect(ui->actiontemp_store, &QAction::triggered, mainSideBar, &MainSideBar::request_cached);
	connect(ui->actionload, &QAction::triggered, mainSideBar, &MainSideBar::load_file);
	connect(ui->actionsave, &QAction::triggered, mainSideBar, &MainSideBar::save_file);
	connect(ui->actionbold, &QAction::triggered, mainSideBar, &MainSideBar::makeBold);
	connect(ui->actionitalic, &QAction::triggered, mainSideBar, &MainSideBar::makeItalic);
	connect(ui->actionunderline, &QAction::triggered, mainSideBar, &MainSideBar::makeUnderline);
}
