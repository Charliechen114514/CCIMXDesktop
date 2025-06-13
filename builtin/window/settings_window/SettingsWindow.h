#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include <QMainWindow>

namespace Ui {
class SettingsWindow;
}

class DesktopMainWindow;
class ConfigureUiPairs;

/**
 * @brief Main window class for the settings interface.
 * 
 * Provides the user interface and logic for configuring application settings.
 */
class SettingsWindow : public QMainWindow {
    Q_OBJECT

public:
    /**
     * @brief Constructs the settings window.
     * @param window Pointer to the main desktop window.
     * @param parent Optional parent widget.
     */
    explicit SettingsWindow(DesktopMainWindow* window, QWidget* parent = nullptr);

    /**
     * @brief Destructor for SettingsWindow.
     */
    ~SettingsWindow();

private:
    /**
     * @brief Sets up signal-slot connections for UI elements.
     */
    void setup_connections();

    /**
     * @brief Initializes and configures UI panels and widgets.
     */
    void setup_panel();

    Ui::SettingsWindow* ui;                 ///< Pointer to the UI form.
    ConfigureUiPairs* pairs;                ///< Object managing UI configuration pairs.
    DesktopMainWindow* handling_window;    ///< Pointer to the main desktop window being handled.
};

#endif // SETTINGSWINDOW_H
