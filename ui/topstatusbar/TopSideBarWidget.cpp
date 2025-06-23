#include "TopSideBarWidget.h"
#include "StatusBarIconWidget.h"
#include "builtin/core/netability_scanner/NetAbilityScanner.h"
#include "desktopmainwindow.h"
#include "netstat/NetStatusChangedEvent.h"
#include "ui_TopSideBarWidget.h"
TopSideBarWidget::TopSideBarWidget(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::TopSideBarWidget) {
	ui->setupUi(this);
    setFixedHeight(this->selfHeight);
}

TopSideBarWidget::~TopSideBarWidget() {
	delete ui;
}

void TopSideBarWidget::installHookedWindow(DesktopMainWindow* mainWindow) {
    this->mainWindow = mainWindow;
    initLeftHandside();
    initRightHandside();
}

void TopSideBarWidget::append_to_toolside(StatusBarIconWidget* src, AcceptPosition position) {
    QWidget* which_widget = nullptr;
    switch (position) {
    case AcceptPosition::LeftSide:
        which_widget = ui->leftsode_widgetbar;
        break;
    case AcceptPosition::RightSide:
        which_widget = ui->rightside_widgetbar;
        break;
    }
    which_widget->layout()->addWidget(src);
}

void TopSideBarWidget::handle_possibleEvent(IconEvent* events) {
    for (auto each : std::as_const(iconsWidgets)) {
        if (each->processIconsEvent(events)) {
            break; // event accepts, quit the sessions
        }
    }
}

#include "netstat/NetStatusStatusBarIconWidget.h"
void TopSideBarWidget::initLeftHandside() {
}

void TopSideBarWidget::initRightHandside() {
    StatusBarIconWidget* netIcon = new NetStatusStatusBarIconWidget(this);
    append_to_toolside(netIcon, AcceptPosition::RightSide);
    iconsWidgets << netIcon;
    connect(mainWindow->netAbilityScanner(),
            &NetAbilityScanner::postStatus, this, [=](NetWorkState state) {
                NetStatusChangedEvent event(netIcon, this);
                event.status = state;
                handle_possibleEvent(&event);
            });
}
