#include "NetMainWindow.h"
#include "ui/MainShowWidget.h"
#include "ui/ToolBoxs.h"
#include "ui_NetMainWindow.h"

NetMainWindow::NetMainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::NetMainWindow) {
	ui->setupUi(this);
	toolbox = new ToolBoxs(this);
	mainWidget = new MainShowWidget(this);
	ui->centralwidget->addLayout({ toolbox }, SideBarWidget::Role::SideBar);
	ui->centralwidget->addLayout({ mainWidget }, SideBarWidget::Role::MainSide);
	mainWidget->show_interfaces();
	connect(toolbox, &ToolBoxs::indicate_show, this, [this](ToolBoxs::ShowType showType) {
		switch (showType) {
		case ToolBoxs::ShowType::PINGER:
			mainWidget->show_pinger();
			break;
		case ToolBoxs::ShowType::SCANNER:
			mainWidget->show_scanner();
			break;
		case ToolBoxs::ShowType::INTERFACES:
			mainWidget->show_interfaces();
			break;
		}
	});
	connect(ui->actionexit, &QAction::triggered, this, &NetMainWindow::close);
	connect(ui->actionsidebar, &QAction::triggered, this, &NetMainWindow::flipSideBar);
}

NetMainWindow::~NetMainWindow() {
	delete ui;
}

void NetMainWindow::resizeEvent(QResizeEvent*) {
	ui->centralwidget->resize(this->size());
}

void NetMainWindow::flipSideBar() {
	sideBarShow = !sideBarShow;
	sideBarShow ? ui->centralwidget->showSideBar() : ui->centralwidget->hideSideBar();
}
