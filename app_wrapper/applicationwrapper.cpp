#include <QFile>
#include <QMainWindow>
#include <QProcess>
#include "applicationwrapper.h"

using ApplicationDepatchResult = ApplicationWrapper::ApplicationDepatchResult;
using ApplicationFinishResult = ApplicationWrapper::ApplicationFinishResult;

namespace {

ApplicationDepatchResult
def_indicate(ApplicationWrapper* wrapper)
{
    ApplicationWrapper::ApplicationDepatchResult res;

    if(!QFile::exists(wrapper->get_app_path())){
        // then the file is not existed
        res.app_depatch_result = ApplicationDepatchResult::AppDepatchResult::APP_FILE_MISSING;
        res.depatched = false;
    }else{
        res.depatched = true;
    }

    return res;
}

ApplicationFinishResult
create_from_raw(int exitCode, QProcess::ExitStatus status){
    ApplicationFinishResult res;
    switch(status){
    case QProcess::ExitStatus::NormalExit:
        res.app_result = ApplicationFinishResult::AppFinishResult::QUIT_NORMAL;
    break;
    default:
        res.app_result = ApplicationFinishResult::AppFinishResult::QUIT_OTHER;
    break;
    }

    res.exit_code = exitCode;
    return res;
}

};

void ApplicationWrapper::do_fin_hook(int exitCode, QProcess::ExitStatus status){
    /* no matter what, process should be delete */
    appProcess->deleteLater();

    if(rawAppFinHook) {
        /* monitor the handling */
        rawAppFinHook(this, exitCode, status);
    }else{
        /* do the default then */
        mainWindow->show();
        ApplicationFinishResult r = create_from_raw(exitCode, status);
        emit app_finished(r);
    }
}

void ApplicationWrapper::def_error_handler()
{
    /* clean up everythings */
    appProcess->deleteLater();

    /* emit the processing signals */

    ApplicationWrapper::ApplicationDepatchResult result;
    result.someOtherDetails = appProcess->errorString();

    emit app_depatch_status(result);

    /* and went back the window */
    mainWindow->show();
}

ApplicationWrapper::
ApplicationWrapper(QObject *parent, QMainWindow *desktopWindow):
    QObject(parent)
{
    mainWindow = desktopWindow;
    pre_indicate = def_indicate;
}

void
ApplicationWrapper::depatch_app()
{
    /* we need to promise the app is exsited */
    if(pre_indicate)
    {
        ApplicationDepatchResult result = pre_indicate(this);
        if(!result.depatched){
            emit app_depatch_status(result);
        }
    }

    /* precheck is passed then */
    appProcess = new QProcess(this);
    connect(appProcess, &QProcess::finished,
            this, &ApplicationWrapper::do_fin_hook);

    /* hide the window for the new process start */
    mainWindow->hide();

    appProcess->start(app_path, app_args);
    ApplicationDepatchResult result;
    if (!appProcess->waitForStarted()) {
        if(error_handler){
            error_handler(this);
        }else{
            def_error_handler();
        }
    }
}
