#ifndef APPLICATIONWRAPPER_H
#define APPLICATIONWRAPPER_H
#include <QObject>
#include <QProcess>
class QMainWindow;
class AppWidget;
/* App Wrapper here */
/* is the Process Wrapper */
class ApplicationWrapper : public QObject {
	Q_OBJECT
public:
	explicit ApplicationWrapper(
		QObject* parent, QMainWindow* desktopWindow);
	/* is the only */
	Q_DISABLE_COPY(ApplicationWrapper);

	/**
	 * @brief The ApplicationDepatchResult class indicate the
	 * app depatching result, for the desktop front end, this can be
	 * used in inform the user what is going on
	 */
	struct ApplicationDepatchResult {
		enum class AppDepatchResult {
			APP_RUN_OK,
			APP_FILE_MISSING,
			APP_OTHER_ERROR
		};

		AppDepatchResult app_depatch_result; ///< Application Result Code
		bool depatched { false }; ///< application depathed resukt
		QString someOtherDetails {}; ///< details informations
	};

	/**
	 * @brief The ApplicationFinishResult class marks the
	 * application depatching result, a typical scene of using this is, when
	 * your app if finished(MainAppWindow Close, or anything trigger the exit functions will make
	 * a process ends, this will emit the signals of AppProcess Finish signals)
	 */
	struct ApplicationFinishResult {
		enum class AppFinishResult {
			QUIT_NORMAL,
			QUIT_OTHER
		};

		AppFinishResult app_result; ///< App Runnning result
		int exit_code; ///< exit code of the application
	};

	/**
	 * @brief App Widget mappings bindings
	 * @param appWidget
	 */
	void bindAppWidget(AppWidget* appWidget) noexcept { this->appWidget = appWidget; }
	/**
	 * @brief app_widget getters of the appWidgets
	 * @return
	 */
	AppWidget* app_widget(void) const { return this->appWidget; }

	/* AppCode is using to identify the app quickly */
	using AppCode = int;
	/**
	 * @brief install the code apps, this will be used soon or later
	 * @param code codes waiting install
	 */
	void install_app_code(AppCode code) noexcept { internal_app_code = code; }
	/**
	 * @brief get the app code
	 * @return app codes
	 */
	AppCode app_code() const { return internal_app_code; }

	/**
	 * @brief app path setter, this will indicate the ELF/PE Executables path in FileSystem
	 * to make this launchable, it must be checkable for QFile, else, we can not fire the process
	 * @param app_path where is the app? :)
	 */
	inline void set_app_path(const QString& app_path) noexcept { this->app_path = app_path; }
	/**
	 * @brief get the app path
	 * @return the app path
	 */
	inline QString get_app_path(void) const { return app_path; }

	/**
	 * @brief app args setter, this will indicate the arguments that is passed to the application
	 * @param args arguments that is passed to the application
	 */
	inline void install_args(const QStringList& l) noexcept { app_args = l; }
	/**
	 * @brief get the args
	 * @return the args
	 */
	inline QStringList args(void) const { return app_args; }

	/**
	 * @brief process_handle
	 * @return
	 * @note:for those who wanna see the detailed process,
	 * use this to fetch the handle
	 */
	inline QProcess* process_handle(void) const { return appProcess; }

	/**
	 * @brief ApplicationWrapper::depatch_app
	 * this is the main function to depatch the application, core functions
	 * 	 */
	void depatch_app(void);

	/* specified settings */
	/* we accept the whole app wrapper and the prelaunch indicate
	 * whether we should launch the application, at default, only
	 * app file exsitance will be checked
	 */
	using PreLaunchIndicate = ApplicationDepatchResult (*)(ApplicationWrapper* wrapper);

	/**
	 * @brief this functions installed the specified behaviours of the prelaunch
	 * @param precheck functions is required
	 * @note this is a hook for the prelaunch, you can use this to specify the launch result callbacks
	 * result can be handle for checking the situations
	 */
	inline void install_prelaunched(PreLaunchIndicate precheck) { pre_indicate = precheck; }

	/* if you wanna do your own jobs, that is required to override this */
	using HandlingFinHook = void (*)(ApplicationWrapper* wrapper, int exit_hook, QProcess::ExitStatus status);
	inline void install_finhook(HandlingFinHook hook) { rawAppFinHook = hook; }

	/* for app depatch level error, we have to expose an interface */
	using ErrorDepatchHook = void (*)(ApplicationWrapper* wrapper);
	/* if you wanna pass out the status, use emit app_depatch_status */
	inline void install_error_handler(ErrorDepatchHook hook) { error_handler = hook; }
signals:
	/* app is depatched or not, see the signals */
	void app_depatch_status(ApplicationWrapper::ApplicationDepatchResult);
	/* app is finished, connect this signals for the hook */
	void app_finished(ApplicationWrapper::ApplicationFinishResult);

private:
	QMainWindow* mainWindow;
	QProcess* appProcess { nullptr };

	QString app_path; ///< Application path that is searchable
	QStringList app_args; ///< If an application is start with args required, this vars hold the cases
	AppCode internal_app_code; ///< Application codes
	AppWidget* appWidget; ///< Binding appWidgets, someTimes if we wanna get the Ui Bindings, this hold the apps

	PreLaunchIndicate pre_indicate; ///< Application prelaunch indicate
	HandlingFinHook rawAppFinHook { nullptr }; ///< Application finish hook
	ErrorDepatchHook error_handler { nullptr }; ///< Application error handler
	/**
	 * @brief Do Process Exit hooks
	 * @param exitCode
	 * @param status
	 */
	void do_fin_hook(int exitCode, QProcess::ExitStatus status);
	/**
	 * @brief This is the default error handler when application
	 * depatching failed
	 */
	void def_error_handler();
};

#endif // APPLICATIONWRAPPER_H
