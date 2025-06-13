#ifndef SETTINGSAPP_H
#define SETTINGSAPP_H

#include "app_wrapper/applicationwrapper.h"
#include "appwidget.h"

class DesktopMainWindow;

/**
 * @brief Wrapper class to launch the settings application.
 * 
 * Manages the initialization and dispatch of the settings application window.
 */
class SettingsLaunch : public ApplicationWrapper {
    Q_OBJECT
public:
    /**
     * @brief Constructs the SettingsLaunch object.
     * @param parent Pointer to the main desktop window.
     */
    explicit SettingsLaunch(DesktopMainWindow* parent);

    /**
     * @brief Dispatches the settings application.
     * 
     * Overrides the base class method to handle specific launch behavior.
     */
    void depatch_app() override;

signals:
    /**
     * @brief Signal emitted to indicate that the settings window should be opened.
     */
    void indicate_open_settings_window();
};

/**
 * @brief Widget class representing the settings application UI.
 */
class SettingsApp : public AppWidget {
    Q_OBJECT
public:
    /**
     * @brief Constructs the SettingsApp widget.
     * @param parent Pointer to the main desktop window or parent widget.
     */
    explicit SettingsApp(DesktopMainWindow* parent = nullptr);

    /**
     * @brief Executes the dispatch operation for the settings app.
     * 
     * Overrides base class method to provide custom dispatch logic.
     */
    void do_daptch() override;

signals:
    /**
     * @brief Signal emitted to indicate that the settings window should be opened.
     */
    void indicate_open_settings_window();
};

#endif // SETTINGSAPP_H

