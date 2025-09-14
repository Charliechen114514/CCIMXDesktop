#include "clockwindow.h"
#include "./ui_clockwindow.h"
#include "alarmynote.h"
#include "alarmynotifier.h"
#include "clockeventbroadcaster.h"
#include "clockwidget.h"
#include "globaltimersrc.h"
#include "timercreatorwindow.h"
#include "toolsbar.h"

ClockWindow::ClockWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::ClockWindow) {
	ui->setupUi(this);
    init_core();
    init_connection();
    init_window();
}

ClockWindow::~ClockWindow() {
	delete ui;
}

void ClockWindow::popup_create_window() {
    if(!creator_window){
        creator_window = new TimerCreatorWindow(this);
		connect(creator_window, &TimerCreatorWindow::notifyNewTimer,
		        this, [this](AlarmyNote* note) {
			        qDebug() << "Install a New Timer";
			        notifier->installAlarmyTime(std::shared_ptr<AlarmyNote>(note));
                    toolBar->installNewEditTimeWidget(note->getTimer());
                });
	}
	creator_window->show();
}

void ClockWindow::init_core()
{
    global_src = new GlobalTimerSrc(this);
    clockWidget = new ClockWidget(this);
    notifier = new AlarmyNotifier(this);
	broadcaster = new ClockEventBroadcaster(this);
	connect(notifier, &AlarmyNotifier::notifyTimeStart,
	        broadcaster, &ClockEventBroadcaster::process_activate_clock);
}

void ClockWindow::init_window()
{
    toolBar = new ToolsBar(notifier, this);
    ui->centralwidget->addLayout({ toolBar }, SideBarWidget::Role::SideBar);
    ui->centralwidget->addLayout({ clockWidget  }, SideBarWidget::Role::MainSide);
}

void ClockWindow::init_connection()
{
    connect(ui->actiontoggle_bar, &QAction::triggered,
            this, [this](){
                ui->centralwidget->switch_state();
            });
    connect(global_src, &GlobalTimerSrc::updateTime,
            clockWidget, &ClockWidget::process_update_invokation);

	connect(ui->actionpop_creator_window, &QAction::triggered,
	        this, &ClockWindow::popup_create_window);
}
