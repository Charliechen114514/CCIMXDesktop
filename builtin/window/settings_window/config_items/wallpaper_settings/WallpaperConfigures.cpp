#include "WallpaperConfigures.h"
#include "builtin/window/settings_window/config_items/wallpaper_settings/option_widgets/FixedOptionWidget.h"
#include "builtin/window/settings_window/config_items/wallpaper_settings/option_widgets/SequenciedSettingsWidget.h"
#include "desktopmainwindow.h"
#include "ui_WallpaperConfigures.h"
#include <QMessageBox>

WallpaperConfigures::WallpaperConfigures(DesktopMainWindow* parent)
    : QWidget(parent)
    , ui(new Ui::WallpaperConfigures) {
	ui->setupUi(this);
    this->window = parent;
    install_settings_widgets();
    auto wallpaperEngine = window->queryWallpaperEngine();
    connect(wallpaperEngine, &WallPaperEngine::wallpaperChanged,
            this, [this](const QPixmap& pixmap) {
                ui->pixmap_label->setPixmap(pixmap);
            });
    WallPaperEngine::SwitchingMode mode = wallpaperEngine->current_mode();
    prev_mode = mode;
    setMode(mode);
    connect(ui->mode_selections, &QComboBox::textActivated,
            this, &WallpaperConfigures::handle_combox_selections);
}

WallpaperConfigures::~WallpaperConfigures() {
	delete ui;
}

void WallpaperConfigures::setMode(const WallPaperEngine::SwitchingMode mode) {
    this->current_mode = mode;
    blockSignals(true);
    ui->mode_selections->setCurrentText(window->queryWallpaperEngine()->modeMappings.toString(mode));
    blockSignals(false);
    QWidget* widget = settings_widgets.value(mode);
    auto engine = window->queryWallpaperEngine();
    auto possible_sq = dynamic_cast<SequenciedSettingsWidget*>(widget);
    if (possible_sq) {
        possible_sq->flush_with_non_path(engine->get_image_list());
        possible_sq->setWallpaper_switch_time(engine->switch_interval());
        possible_sq->setAnimation_duration(engine->animation_speed());
    }

    auto possible_fix = dynamic_cast<FixedOptionWidget*>(widget);
    if (possible_fix) {
        possible_fix->setPixmap(engine->get_current_pixmap());
    }

    ui->stackedWidget->setCurrentWidget(widget);
}

void WallpaperConfigures::handle_combox_selections(const QString& text) {
    WallPaperEngine::SwitchingMode mode;
    try {
        mode = window->queryWallpaperEngine()->modeMappings.fromString(text);
    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Error Occurs!", "Can not handle the mode of " + text + " Request an Issue to report bugs");
        return;
    }
    setMode(mode);
}

void WallpaperConfigures::apply_settings() {
    prev_mode = current_mode;
    QWidget* widget = settings_widgets.value(current_mode);
    switch (current_mode) {
    case WallPaperEngine::SwitchingMode::Fixed: {
        FixedTypeWallPaperSettings* settings = new FixedTypeWallPaperSettings();
        auto possible_fix = dynamic_cast<FixedOptionWidget*>(widget);
        settings->map = possible_fix->get_pixmap();
        settings->mode = current_mode;
        window->process_wallpaper_settings(settings);
    } break;
    case WallPaperEngine::SwitchingMode::Movement:
    case WallPaperEngine::SwitchingMode::Gradient: {
        FlowTypeTypeWallPaperSettings* settings = new FlowTypeTypeWallPaperSettings();
        auto possible_sq = dynamic_cast<SequenciedSettingsWidget*>(widget);
        settings->images = possible_sq->get_image_lists();
        settings->mode = current_mode;
        settings->animation_speed = possible_sq->getAnimation_duration();
        settings->switch_interval = possible_sq->getWallpaper_switch_time();
        settings->curve = possible_sq->get_easingcurve_type();
        window->process_wallpaper_settings(settings);
    } break;
    }
}

void WallpaperConfigures::install_settings_widgets() {
    auto wid = new FixedOptionWidget(this);
    settings_widgets.insert(WallPaperEngine::SwitchingMode::Fixed, wid);
    ui->stackedWidget->addWidget(wid);
    auto other_wid = new SequenciedSettingsWidget(this);
    settings_widgets.insert(WallPaperEngine::SwitchingMode::Gradient, other_wid);
    ui->stackedWidget->addWidget(other_wid);
    other_wid = new SequenciedSettingsWidget(this);
    settings_widgets.insert(WallPaperEngine::SwitchingMode::Movement, other_wid);
    ui->stackedWidget->addWidget(other_wid);
    ui->mode_selections->addItems(window->queryWallpaperEngine()->modeMappings.values());
}

void WallpaperConfigures::on_btn_reset_clicked() {
    setMode(prev_mode);
}

void WallpaperConfigures::on_btn_apply_clicked() {
    apply_settings();
}
