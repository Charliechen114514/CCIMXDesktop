#ifndef APPLAUNCHERAPP_H
#define APPLAUNCHERAPP_H

#include <appwidget.h>

#include "app_wrapper/applicationwrapper.h"
#include "appwidget.h"

class DesktopMainWindow;

/**
 * @brief Wrapper class to launch the settings application.
 *
 * Manages the initialization and dispatch of the settings application window.
 */
class AppLaunchLauncher : public ApplicationWrapper {
    Q_OBJECT
public:
    /**
     * @brief Constructs the AppLaunchLauncher object.
     * @param parent Pointer to the main desktop window.
     */
    explicit AppLaunchLauncher(DesktopMainWindow* parent);

    /**
     * @brief Dispatches the settings application.
     *
     * Overrides the base class method to handle specific launch behavior.
     */
    void depatch_app() override;

signals:
    /**
     * @brief Signal emitted to indicate that the launch window should be opened.
     */
    void indicate_open_launch_window();
};

/**
 * @brief Widget class representing the settings application UI.
 */
class AppLauncherApp : public AppWidget {
    Q_OBJECT
public:
    /**
     * @brief Constructs the AppLauncherApp widget.
     * @param parent Pointer to the main desktop window or parent widget.
     */
    explicit AppLauncherApp(DesktopMainWindow* parent = nullptr);

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
    void indicate_open_launch_window();
};

#endif // APPLAUNCHERAPP_H
