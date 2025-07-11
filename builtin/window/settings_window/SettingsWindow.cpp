#include "SettingsWindow.h"
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
    connect(ui->actionquit, &QAction::triggered, this, &SettingsWindow::hide);
}

#include "builtin/window/settings_window/config_items/wallpaper_settings/WallpaperConfigures.h"
#include "config_items/appwidgets_globalconfig/AppWidgetConfigures.h"
#include "config_items/light_controller/LightConfigures.h"
#include "config_items/slide_settings/SlideSettings.h"
#include "config_items/topsidebar/TopSideBarWidgetConfigures.h"
#include "config_items/topsidebar/timesettings/TimeLabelSettings.h"
void SettingsWindow::setup_panel() {
    pairs = new ConfigureUiPairs(ui->treeWidget, ui->stackedWidget);
    auto app_widgets_configs = new AppWidgetConfigures(handling_window, this);
    QTreeWidgetItem* appwidgets_config_items = pairs->install_mappings("AppWidget", nullptr, app_widgets_configs);
    pairs->install_mappings("Fonts", appwidgets_config_items, app_widgets_configs);
    pairs->install_mappings("Icons", appwidgets_config_items, app_widgets_configs);

    pairs->install_mappings("Backlights", nullptr, new LightConfigures(this));
    pairs->install_mappings("WallPaper", nullptr, new WallpaperConfigures(handling_window));

    auto top_sidebar = pairs->install_mappings("TopSideBar", nullptr, new TopSideBarWidgetConfigures(handling_window));
    pairs->install_mappings("TimeLabelSettings", top_sidebar, new TimeLabelSettings(handling_window));

    pairs->install_mappings("Slide Settings", nullptr, new SlideSettings(handling_window));
}
