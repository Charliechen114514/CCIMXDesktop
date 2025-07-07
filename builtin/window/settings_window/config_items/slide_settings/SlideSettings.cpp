#include "SlideSettings.h"
#include "core/page_switching_limiter/PageSwitchingLimiter.h"
#include "ui/desktopmainwindow.h"
#include "ui_SlideSettings.h"
SlideSettings::SlideSettings(DesktopMainWindow* parent)
    : QWidget(parent)
    , ui(new Ui::SlideSettings)
    , window(parent) {
	ui->setupUi(this);
    limitive_controller = new PageSwitchingLimiter(ui->slider_of_slidegap, this);
    ui->value_mark_label->setText("current: " + QString::number(window->get_slide_limitive()));
    connect(limitive_controller, &PageSwitchingLimiter::valueChanged,
            this, [this](int value) {
                ui->value_mark_label->setText("current: " + QString::number(value));
                window->set_slide_limitive(value);
            });
}

SlideSettings::~SlideSettings() {
	delete ui;
}
