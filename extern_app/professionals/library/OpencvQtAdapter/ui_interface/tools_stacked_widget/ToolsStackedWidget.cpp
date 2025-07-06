#include "ToolsStackedWidget.h"
#include "ui_ToolsStackedWidget.h"

ToolsStackedWidget::ToolsStackedWidget(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::ToolsStackedWidget) {
	ui->setupUi(this);
    Q_INIT_RESOURCE(ui_sources);
}

ToolsStackedWidget::~ToolsStackedWidget() {
	delete ui;
}

void ToolsStackedWidget::add_switchable_page(const PagePackage& package) {
    ToolLeftWidgets::ToolButtonInstallPackage installer = {
        package.name,
        package.icon,
        [this, package]() {
            ui->stackedWidget->setCurrentWidget(package.widget);
        }
    };

    ui->widget->install_toolbuttons(installer);
    ui->stackedWidget->addWidget(package.widget);
}
