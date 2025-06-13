#ifndef WALLPAPERCONFIGURES_H
#define WALLPAPERCONFIGURES_H

#include "core/wallpaper/WallPaperEngine.h"
#include <QWidget>

class DesktopMainWindow;

namespace Ui {
class WallpaperConfigures;
}

/**
 * @brief The WallpaperConfigures class
 * Provides configuration options for managing wallpaper switching behavior.
 * 
 * This class allows users to choose wallpaper switching modes and 
 * configure related parameters through the associated UI.
 */
class WallpaperConfigures : public QWidget {
    Q_OBJECT

public:
    /**
     * @brief Constructs the WallpaperConfigures widget.
     * @param parent Pointer to the main desktop window.
     */
    explicit WallpaperConfigures(DesktopMainWindow* parent);

    /**
     * @brief Destructor.
     */
    ~WallpaperConfigures();

    /**
     * @brief Sets the wallpaper switching mode.
     * @param mode The desired switching mode.
     */
    void setMode(const WallPaperEngine::SwitchingMode mode);

private slots:
    /**
     * @brief Handles combo box selections for wallpaper switching mode.
     * @param text Selected text from the combo box.
     */
    void handle_combox_selections(const QString& text);

    /**
     * @brief Applies the current wallpaper configuration settings.
     */
    void apply_settings();

    /**
     * @brief Resets the settings to defaults.
     */
    void on_btn_reset_clicked();

    /**
     * @brief Applies changes and updates the wallpaper engine.
     */
    void on_btn_apply_clicked();

private:
    Ui::WallpaperConfigures* ui;     ///< UI components pointer.
    DesktopMainWindow* window;       ///< Reference to the main window.
    WallPaperEngine::SwitchingMode current_mode; ///< Current selected mode.
    WallPaperEngine::SwitchingMode prev_mode;    ///< Previously active mode.
    QMap<WallPaperEngine::SwitchingMode, QWidget*> settings_widgets; ///< Widget mappings for each mode.

    /**
     * @brief Installs configuration widgets for each switching mode.
     */
    void install_settings_widgets();
};

#endif // WALLPAPERCONFIGURES_H
