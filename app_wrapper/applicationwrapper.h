#ifndef APPLICATIONWRAPPER_H
#define APPLICATIONWRAPPER_H
#include <QObject>
#include <QProcess>
class QMainWindow;
class AppWidget;
/* App Wrapper here */
/* is the Process Wrapper */
class ApplicationWrapper : public QObject
{
    Q_OBJECT
public:
    explicit ApplicationWrapper(
        QObject* parent, QMainWindow* desktopWindow);
    /* is the only */
    Q_DISABLE_COPY(ApplicationWrapper);
    struct ApplicationDepatchResult {
        enum class AppDepatchResult {
            APP_RUN_OK,
            APP_FILE_MISSING,
            APP_OTHER_ERROR
        };

        AppDepatchResult    app_depatch_result;
        bool                depatched{false};
        QString             someOtherDetails{};
    };

    struct ApplicationFinishResult {
        enum class AppFinishResult{
            QUIT_NORMAL,
            QUIT_OTHER
        };

        AppFinishResult app_result;
        int             exit_code;
    };

    /* bind AppWidget */
    void                bindAppWidget(AppWidget* appWidget) noexcept {this->appWidget = appWidget;}
    AppWidget*          app_widget(void) const {return this->appWidget;}

    /* AppCode is using to identify the app quickly */
    using               AppCode = int;
    void                install_app_code(AppCode code) noexcept {internal_app_code = code;}
    AppCode             app_code() const {return internal_app_code;}

    inline void         set_app_path(const QString& app_path) noexcept{this->app_path = app_path;}
    /* get the app path */
    inline QString      get_app_path(void) const {return app_path;}

    inline void         install_args(const QStringList& l) noexcept {app_args = l;}
    inline QStringList  args(void) const {return app_args;}

    /* for those who wanna see the detailed process,
     * use this to fetch the handle */
    inline QProcess*    process_handle(void) const {return appProcess;}

    /* Application Depatcher */
    void                depatch_app(void);

    /* specified settings */
    /* we accept the whole app wrapper and the prelaunch indicate
     * whether we should launch the application, at default, only
     * app file exsitance will be checked
     */
    using                       PreLaunchIndicate =
        ApplicationDepatchResult(*)(ApplicationWrapper* wrapper);
    /* result can be handle for checking the situations */
    inline void install_prelaunched(PreLaunchIndicate   precheck){pre_indicate = precheck;}

    /* if you wanna do your own jobs, that is required to override this */
    using       HandlingFinHook = void(*)(ApplicationWrapper* wrapper, int exit_hook, QProcess::ExitStatus status);
    inline void install_finhook(HandlingFinHook hook){rawAppFinHook = hook;}

    /* for app depatch level error, we have to expose an interface */
    using       ErrorDepatchHook = void(*)(ApplicationWrapper* wrapper);
    /* if you wanna pass out the status, use emit app_depatch_status */
    inline void install_error_handler(ErrorDepatchHook hook){error_handler = hook;}
signals:
    /* app is depatched or not, see the signals */
    void        app_depatch_status(ApplicationWrapper::ApplicationDepatchResult);
    /* app is finished, connect this signals for the hook */
    void        app_finished(ApplicationWrapper::ApplicationFinishResult);

private:

    QMainWindow*        mainWindow;
    QProcess*           appProcess{nullptr};

    QString             app_path;
    QStringList         app_args;
    AppCode             internal_app_code;
    AppWidget*          appWidget;

    PreLaunchIndicate   pre_indicate;
    HandlingFinHook     rawAppFinHook{nullptr};
    ErrorDepatchHook    error_handler{nullptr};

    void                do_fin_hook(int exitCode, QProcess::ExitStatus status);
    void                def_error_handler();

};

#endif // APPLICATIONWRAPPER_H
