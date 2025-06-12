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
    friend bool operator==(const ApplicationWrapper& application_wrapper_a, const ApplicationWrapper& application_wrapper_b) {
        return application_wrapper_a.internal_app_code == application_wrapper_b.internal_app_code;
    }

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
    using AppCode = QString;

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
    virtual void depatch_app();

    /**
     * @brief depatchable
     * @return if the app is actually internal depatchable;
     */
    virtual bool depatchable() { return mainWindow; }

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

private:
	DesktopMainWindow* mainWindow; ///< mainWindow holders for hooking
	QProcess* appProcess { nullptr }; ///< appProcess instance in process level

	QString app_path; ///< Path to the application executable.
	QStringList app_args; ///< Arguments passed to the application.
	AppCode internal_app_code; ///< Internal code identifying the app.
	AppWidget* appWidget; ///< UI widget associated with the app.

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
