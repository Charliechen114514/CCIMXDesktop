#include "homepage.h"
#include "builtin/core/global_clock_src/GlobalClockSources.h"
#include "desktopmainwindow.h"
#include "ui_homepage.h"
HomePage::HomePage(DesktopMainWindow* parent)
    : QWidget(parent)
    , ui(new Ui::HomePage) {
    ui->setupUi(this);
    GlobalClockSources* src = parent->clock_src();
    ClockWidget* clockWidget = clock_widget();
    connect(src, &GlobalClockSources::timeUpdate,
            clockWidget, &ClockWidget::process_update_invokation);

    DigitalTimeWidget* digital = digital_timeWidget();
    connect(src, &GlobalClockSources::timeUpdate,
            digital, &DigitalTimeWidget::process_time_update);
}

QWidget* HomePage::expected_appcards_widgets() const {
    return ui->right_bottom_widget;
}

ClockWidget* HomePage::clock_widget() const {
    return ui->left_top_widget;
}

DigitalTimeWidget* HomePage::digital_timeWidget() const {
    return ui->left_bottom_widget;
}

HomePage::~HomePage() {
    delete ui;
}

CardStackWidget* HomePage::card_stack_widget() const {
    return ui->stackedWidget;
}
