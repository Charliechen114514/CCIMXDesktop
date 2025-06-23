#include "TopSideBarWidget.h"
#include "StatusBarIconWidget.h"
#include "desktop_settings.h"
#include "desktopmainwindow.h"
#include "netstat/NetStatusChangedEvent.h"
#include "ui_TopSideBarWidget.h"
TopSideBarWidget::TopSideBarWidget(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::TopSideBarWidget) {
	ui->setupUi(this);
    setHeight(TOPSIDEBAR_HEIGHT);
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

StatusBarIconWidget* TopSideBarWidget::queryFromName(const QString& name) {
    auto it = std::find_if(iconsWidgets.begin(), iconsWidgets.end(), [name](StatusBarIconWidget* widget) {
        return widget->labeledName() == name;
    });

    return (it != iconsWidgets.end()) ? *it : // yes we find it!
        nullptr; // no, we returns nullptr
}

void TopSideBarWidget::setHeight(const int height) {
    this->selfHeight = qBound(TOPSIDEBAR_HEIGHT_MIN, height, TOPSIDEBAR_HEIGHT_MAX);
    setFixedHeight(this->selfHeight);
}

int TopSideBarWidget::height_min() const {
    return TOPSIDEBAR_HEIGHT_MIN;
}

int TopSideBarWidget::height_max() const {
    return TOPSIDEBAR_HEIGHT_MAX;
}

#include "battery/BatteryStatusbarIcon.h"
#include "builtin/core/global_clock_src/GlobalClockSources.h"
#include "builtin/core/netability_scanner/NetAbilityScanner.h"
#include "netstat/NetStatusStatusBarIconWidget.h"
#include "time_display/TimeDisplayIconWidget.h"
void TopSideBarWidget::initLeftHandside() {
    auto position = AcceptPosition::LeftSide;
    TimeDisplayIconWidget* timeIcon = new TimeDisplayIconWidget(this);
    append_to_toolside(timeIcon, position);
    iconsWidgets << timeIcon;
    auto clk_src = mainWindow->clock_src();
    connect(clk_src, &GlobalClockSources::timeUpdate,
            timeIcon, &TimeDisplayIconWidget::update_displayTime);
}

void TopSideBarWidget::initRightHandside() {
    auto position = AcceptPosition::RightSide;

    // net stat
    StatusBarIconWidget* netIcon
        = new NetStatusStatusBarIconWidget(this);
    append_to_toolside(netIcon, position);
    iconsWidgets << netIcon;
    connect(mainWindow->netAbilityScanner(),
            &NetAbilityScanner::postStatus, this, [=](NetWorkState state) {
                NetStatusChangedEvent event(netIcon, this);
                event.status = state;
                handle_possibleEvent(&event);
            });

    // batteries
    StatusBarIconWidget* batteries = new BatteryStatusbarIcon(this);
    append_to_toolside(batteries, position);
    iconsWidgets << batteries;
}
