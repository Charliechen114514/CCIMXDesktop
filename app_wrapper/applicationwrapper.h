#ifndef APPLICATIONWRAPPER_H
#define APPLICATIONWRAPPER_H

#include <QObject>
#include <QProcess>

class DesktopMainWindow;
class AppWidget;

/**
 * @brief The ApplicationWrapper class is the process wrapper.
 *
 * This class manages launching, monitoring, and interacting with
 * external applications through QProcess.
 */
class ApplicationWrapper : public QObject {
    Q_OBJECT
public:
    /**
     * @brief Constructs an ApplicationWrapper instance.
     * @param parent The parent QObject.
     * @param desktopWindow Pointer to the main desktop window.
     */
    explicit ApplicationWrapper(QObject* parent, DesktopMainWindow* desktopWindow);

    /**
     * @brief Disable copy constructor and assignment operator.
     * This class is not copyable.
     */
    Q_DISABLE_COPY(ApplicationWrapper);

    /**
     * @brief The ApplicationDepatchResult struct represents the result
     * of launching (depatching) an application.
     */
    struct ApplicationDepatchResult {
        /**
         * @brief Possible results of application depatch.
         */
        enum class AppDepatchResult {
            APP_RUN_OK,       ///< Application launched successfully
            APP_FILE_MISSING, ///< Application executable file is missing
            APP_OTHER_ERROR   ///< Other errors during launch
        };

        AppDepatchResult app_depatch_result; ///< Result code of application launch
        bool depatched { false };            ///< Whether application was launched
        QString someOtherDetails {};         ///< Additional info or error messages
    };

    /**
     * @brief The ApplicationFinishResult struct represents
     * the result when an application finishes execution.
     */
    struct ApplicationFinishResult {
        /**
         * @brief Possible application finish states.
         */
        enum class AppFinishResult {
            QUIT_NORMAL, ///< Application exited normally
            QUIT_OTHER   ///< Application exited abnormally or other reasons
        };

        AppFinishResult app_result; ///< Application exit result
        int exit_code;              ///< Exit code returned by the application
    };

    /**
     * @brief Bind the UI widget associated with the application.
     * @param appWidget Pointer to the AppWidget instance.
     */
    void bindAppWidget(AppWidget* appWidget) noexcept { this->appWidget = appWidget; }

    /**
     * @brief Returns the bound application widget.
     * @return Pointer to the AppWidget instance.
     */
    AppWidget* app_widget() const { return this->appWidget; }

    /// AppCode is used to uniquely identify applications.
    using AppCode = int;

    /**
     * @brief Sets the app code for quick identification.
     * @param code The app code to install.
     */
    void install_app_code(AppCode code) noexcept { internal_app_code = code; }

    /**
     * @brief Returns the installed app code.
     * @return The app code.
     */
    AppCode app_code() const { return internal_app_code; }

    /**
     * @brief Sets the file system path to the application executable.
     *
     * The path must be accessible and executable for launching the process.
     *
     * @param app_path The file path of the application executable.
     */
    inline void set_app_path(const QString& app_path) noexcept { this->app_path = app_path; }

    /**
     * @brief Returns the application executable path.
     * @return The application path as QString.
     */
    inline QString get_app_path() const { return app_path; }

    /**
     * @brief Sets the arguments to pass to the application on launch.
     * @param args List of arguments.
     */
    inline void install_args(const QStringList& args) noexcept { app_args = args; }

    /**
     * @brief Returns the argument list for the application.
     * @return QStringList of arguments.
     */
    inline QStringList args() const { return app_args; }

    /**
     * @brief Returns the internal QProcess handle.
     * @note Use this to access detailed process control or signals.
     * @return Pointer to QProcess managing the application.
     */
    inline QProcess* process_handle() const { return appProcess; }

    /**
     * @brief Launches the application (depatch).
     *
     * This is the core function to start the external process.
     */
    void depatch_app();

    /// Function pointer type for pre-launch checks.
    using PreLaunchIndicate = ApplicationDepatchResult (*)(ApplicationWrapper* wrapper);

    /**
     * @brief Installs a pre-launch indication hook.
     *
     * This hook can be used to check conditions or prepare before launch.
     *
     * @param precheck The function pointer to the pre-launch check.
     */
    inline void install_prelaunched(PreLaunchIndicate precheck) { pre_indicate = precheck; }

    /// Function pointer type for handling application finish hooks.
    using HandlingFinHook = void (*)(ApplicationWrapper* wrapper, int exit_hook, QProcess::ExitStatus status);

    /**
     * @brief Installs a hook called when the application finishes.
     * @param hook The function pointer to the finish hook.
     */
    inline void install_finhook(HandlingFinHook hook) { rawAppFinHook = hook; }

    /// Function pointer type for handling depatch errors.
    using ErrorDepatchHook = void (*)(ApplicationWrapper* wrapper);

    /**
     * @brief Installs an error handler hook for depatch failures.
     * @param hook The function pointer to the error handler.
     */
    inline void install_error_handler(ErrorDepatchHook hook) { error_handler = hook; }

signals:
    /**
     * @brief Emitted when application depatch status changes.
     * @param result The result of the depatch.
     */
    void app_depatch_status(ApplicationWrapper::ApplicationDepatchResult result);

    /**
     * @brief Emitted when the application finishes.
     * @param result The application finish result.
     */
    void app_finished(ApplicationWrapper::ApplicationFinishResult result);

private:
    DesktopMainWindow* mainWindow; ///< mainWindow holders for hooking
    QProcess* appProcess { nullptr }; ///< appProcess instance in process level

    QString app_path;          ///< Path to the application executable.
    QStringList app_args;      ///< Arguments passed to the application.
    AppCode internal_app_code; ///< Internal code identifying the app.
    AppWidget* appWidget;      ///< UI widget associated with the app.

    PreLaunchIndicate pre_indicate;   ///< Pre-launch check hook.
    HandlingFinHook rawAppFinHook { nullptr }; ///< Application finish hook.
    ErrorDepatchHook error_handler { nullptr }; ///< Application depatch error handler.

    /**
     * @brief Executes the finish hook on process exit.
     * @param exitCode The exit code returned by the process.
     * @param status The exit status.
     */
    void do_fin_hook(int exitCode, QProcess::ExitStatus status);

    /**
     * @brief Default error handler when depatching fails.
     */
    void def_error_handler();
};

#endif // APPLICATIONWRAPPER_H
