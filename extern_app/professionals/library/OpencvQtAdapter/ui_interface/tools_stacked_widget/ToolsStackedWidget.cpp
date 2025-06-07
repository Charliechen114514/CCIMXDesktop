#include "ToolsStackedWidget.h"
#include "ui_ToolsStackedWidget.h"

ToolsStackedWidget::ToolsStackedWidget(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::ToolsStackedWidget) {
	ui->setupUi(this);
    Q_INIT_RESOURCE(sources);
}

ToolsStackedWidget::~ToolsStackedWidget() {
	delete ui;
}

void ToolsStackedWidget::add_switchable_page(const PagePackage& package) {
    ToolLeftWidgets::ToolButtonInstallPackage installer = {
        .name = package.name,
        .icon = package.icon,
        .callback = [this, package]() {
            ui->stackedWidget->setCurrentWidget(package.widget);
        }
    };

    ui->widget->install_toolbuttons(installer);
    ui->stackedWidget->addWidget(package.widget);
}
