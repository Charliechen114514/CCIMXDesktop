#ifndef APPWIDGETCONFIGURES_H
#define APPWIDGETCONFIGURES_H

#include "builtin/window/settings_window/cores/SettingsPack.h"
#include <QWidget>

class AppWidget;
class DesktopMainWindow;

namespace Ui {
class AppWidgetConfigures;
}

/**
 * @brief The AppWidgetConfigures class
 * Provides a settings panel for customizing the appearance and behavior of AppWidgets.
 * 
 * This class allows users to modify settings such as font, color, and size
 * for widgets displayed in the application. It is integrated with the main
 * application window to preview and apply changes.
 */
class AppWidgetConfigures : public QWidget {
    Q_OBJECT

public:
    /**
     * @brief Constructs the AppWidgetConfigures widget.
     * @param window Pointer to the main desktop window for context.
     * @param parent Optional parent QWidget.
     */
    explicit AppWidgetConfigures(DesktopMainWindow* window, QWidget* parent = nullptr);

    /**
     * @brief Destructor.
     */
    ~AppWidgetConfigures();

private slots:
    /**
     * @brief Handles changes in the spinbox for setting size.
     * @param size The new size value.
     */
    void process_spinbox_change(int size);

    /**
     * @brief Handles font selection button click.
     */
    void on_btn_select_font_clicked();

    /**
     * @brief Handles color selection button click.
     */
    void on_btn_select_color_clicked();

private:
    Ui::AppWidgetConfigures* ui;               ///< UI components pointer.
    DesktopMainWindow* window;                 ///< Reference to the main window.
    AppWidget* appWidget;                      ///< The target widget being configured.
    AppWidgetsSettingsInfoPack info;           ///< Holds the current settings.

    /**
     * @brief Loads default styles and updates the preview accordingly.
     */
    void process_default_init_load();
};

#endif // APPWIDGETCONFIGURES_H
