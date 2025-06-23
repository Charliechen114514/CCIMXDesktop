#include "TopSideBarWidgetConfigures.h"
#include "TopSideBarWidget.h"
#include "desktopmainwindow.h"
#include "ui_TopSideBarWidgetConfigures.h"

namespace {
QString display_format(int height) {
    return QString("Height: %1").arg(QString::number(height));
}
}

TopSideBarWidgetConfigures::TopSideBarWidgetConfigures(DesktopMainWindow* parent)
    : QWidget(parent)
    , ui(new Ui::TopSideBarWidgetConfigures) {
	ui->setupUi(this);
    toolsidebar = parent->topSideBar();
    ui->height_slider->setMinimum(toolsidebar->height_min());
    ui->height_slider->setMaximum(toolsidebar->height_max());
    ui->height_slider->setValue(toolsidebar->height());
    ui->height_show_label->setText(display_format(ui->height_slider->value()));
    connect(ui->height_slider, &QSlider::valueChanged,
            this, [this](const int value) {
                toolsidebar->setHeight(value);
                ui->height_show_label->setText(display_format(ui->height_slider->value()));
            });
}

TopSideBarWidgetConfigures::~TopSideBarWidgetConfigures() {
	delete ui;
}
