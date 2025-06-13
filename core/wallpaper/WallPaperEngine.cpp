#include "WallPaperEngine.h"
#include "WallPaperUtilsColliections.h"
#include "core/coretools.h"
#include "desktop_settings.h"
#include "ui/desktopmainwindow.h"
#include "wallpaperanimationhandler.h"
#include <QLabel>
#include <QTimer>

WallPaperEngine::WallPaperEngine(DesktopMainWindow* window)
    : QObject(window) {
    wallpaperLabel = new QLabel(window);
    wallpaperLabel->setScaledContents(true);
    wallpaperLabel->lower();
    wallpaperLabel->setGeometry(0, 0, window->width(), window->height());

    bufferpaperLabel = new QLabel(window);
    bufferpaperLabel->setScaledContents(true);
    bufferpaperLabel->lower();
    bufferpaperLabel->setGeometry(0, 0, window->width(), window->height());
    bufferpaperLabel->hide();
    shoule_be_lower = window->centralWidget();
    reset_defaults();
    invoke_switch_timer = new QTimer(this);
    invoke_switch_timer->setInterval(SWITCH_INTERVAL);
    connect(invoke_switch_timer, &QTimer::timeout,
            this, &WallPaperEngine::process_internal_timer_hook);
    set_mode(this->mode);
}

void WallPaperEngine::process_resize(DesktopMainWindow* window) {
    /* makeups the full screen */
    wallpaperLabel->setGeometry(0, 0, window->width(), window->height());
    bufferpaperLabel->setGeometry(0, 0, window->width(), window->height());
}

void WallPaperEngine::set_switch_interval(int new_interval) {
    invoke_switch_timer->setInterval(new_interval);
}

int WallPaperEngine::switch_interval() const {
    return invoke_switch_timer->interval();
}

void WallPaperEngine::set_mode(const SwitchingMode mode) {
    this->mode = mode;
    switch (this->mode) {
    case SwitchingMode::Gradient:
        invoke_switch_timer->start();
        break;
    case SwitchingMode::Fixed:
        invoke_switch_timer->stop();
        break;
    case SwitchingMode::Movement:
        invoke_switch_timer->start();
        break;
    }
}

QPixmap WallPaperEngine::get_current_pixmap() const {
    switch (this->mode) {
    case SwitchingMode::Movement:
        return bufferpaperLabel->pixmap();
    default:
        return wallpaperLabel->pixmap();
    }
}

void WallPaperEngine::set_showing_pictures(const QPixmap& map) {
    wallpaperLabel->setPixmap(map);
    emit wallpaperChanged(map);
}

void WallPaperEngine::set_animation_duration_second(int secs) {
    animation_durations = secs;
}

int WallPaperEngine::duration_seconds() const {
    return animation_durations;
}

QStringList& WallPaperEngine::get_image_list() {
    return image_lists;
}

void WallPaperEngine::set_image_list(const QStringList& l) {
    image_lists = l;
    default_behaviour_of_flush();
    emit imagelist_changed(image_lists);
}

void WallPaperEngine::reset_defaults() {
    /* Collect from the Image Lists */
    image_lists << CoreTools::enumeratefiles(WALLPAPER_DEFAULT_DIRENT, WallPaperUtilsColliections::prefixs());
    default_behaviour_of_flush();
    emit imagelist_changed(image_lists);
}

void WallPaperEngine::fallback_empty_session() {
    image_lists.clear();
    image_lists << WallPaperUtilsColliections::collect_from_qrcs();
    default_behaviour_of_flush();
    emit imagelist_changed(image_lists);
}

void WallPaperEngine::process_internal_timer_hook() {
    switch (this->mode) {
    case SwitchingMode::Gradient: {
        /* switch the background page */
        WallPaperAnimationHandler::ImagePoolEngine engine;
        engine.image_list = &this->image_lists;
        WallPaperAnimationHandler::process_opacity_switch(this, engine, { animation_durations });
        emit wallpaperChanged(this->wallpaperLabel->pixmap());
    } break;
    case SwitchingMode::Fixed:
        /* can not get here */
        break;
    case SwitchingMode::Movement:
        WallPaperAnimationHandler::ImagePoolEngine engine;
        engine.image_list = &this->image_lists;
        WallPaperAnimationHandler::process_movement_switch(this, engine, { animation_durations });
        emit wallpaperChanged(this->bufferpaperLabel->pixmap());
        break;
    }
}

void WallPaperEngine::default_behaviour_of_flush() {
    if (!image_lists.isEmpty()) {
        /* select randomly, lol */
        wallpaperLabel->setPixmap(
            WallPaperAnimationHandler::ImagePoolEngine::
                default_selections(image_lists));
    } else {
        reset_defaults();
    }
}
