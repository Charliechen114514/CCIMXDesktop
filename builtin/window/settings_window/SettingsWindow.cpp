#include "SettingsWindow.h"
#include "config_items/appwidgets_globalconfig/AppWidgetConfigures.h"
#include "cores/ConfigureUiPairs.h"
#include "ui/desktopmainwindow.h"
#include "ui_SettingsWindow.h"
SettingsWindow::SettingsWindow(DesktopMainWindow* window, QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::SettingsWindow) {
	ui->setupUi(this);
    handling_window = window;
    setup_panel();
    setup_connections();
}

SettingsWindow::~SettingsWindow() {
	delete ui;
}

void SettingsWindow::setup_connections() {
    connect(ui->actionquit, &QAction::triggered, this, &SettingsWindow::close);
}

void SettingsWindow::setup_panel() {
    pairs = new ConfigureUiPairs(ui->treeWidget, ui->stackedWidget);
    auto app_widgets_configs = new AppWidgetConfigures(handling_window, this);
    QTreeWidgetItem* appwidgets_config_items = pairs->install_mappings("AppWidget", nullptr, app_widgets_configs);
    pairs->install_mappings("Fonts", appwidgets_config_items, app_widgets_configs);
    pairs->install_mappings("Icons", appwidgets_config_items, app_widgets_configs);
}
