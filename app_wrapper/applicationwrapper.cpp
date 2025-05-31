#include "applicationwrapper.h"
#include "desktopmainwindow.h"
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QProcess>
using ApplicationDepatchResult = ApplicationWrapper::ApplicationDepatchResult;
using ApplicationFinishResult = ApplicationWrapper::ApplicationFinishResult;

namespace {

/**
 * @brief fileExistsIgnoreSuffix fuck Microsoft, its execution requires
 *  .exe, which, will lead a file missing check
 * @param filePath
 * @return if the file exsited
 */
bool fileExistsIgnoreSuffix(const QString& filePath) {
	QFileInfo fi(filePath);
	QString dirPath = fi.absolutePath();
	QString baseName = fi.completeBaseName();

	QDir dir(dirPath);
	QStringList entryList = dir.entryList(QDir::Files | QDir::NoDotAndDotDot);

	for (const QString& entry : entryList) {
		QFileInfo entryInfo(dir, entry);
		if (entryInfo.completeBaseName() == baseName) {
			return true;
		}
	}
	return false;
}

/**
 * @brief this is the default pre-indicate function, this is the default
 * hook for the application deptaching, if the file is not existed, then
 * it will return the APP_FILE_MISSING status currently now
 * @param wrapper the applications wrapper which is about depatch
 * @return
 */
ApplicationDepatchResult
def_indicate(ApplicationWrapper* wrapper) {
	ApplicationWrapper::ApplicationDepatchResult res;

	if (!fileExistsIgnoreSuffix(wrapper->get_app_path())) {
		// then the file is not existed
		res.app_depatch_result = ApplicationDepatchResult::AppDepatchResult::APP_FILE_MISSING;
		res.depatched = false;
	} else {
		res.app_depatch_result = ApplicationDepatchResult::AppDepatchResult::APP_RUN_OK;
		res.depatched = true;
	}

	return res;
}

/**
 * @brief  the helper of do_fin_hook, adapt from the raw exit code, status to the
 * packaged ApplicationFinishResult
 *
 * @param exitCode: process exiting code
 * @param status: The status with detailed exit, for developers
 * you can modify the function to process a more detailed status handler
 * @return
 */
ApplicationFinishResult
create_from_raw(int exitCode, QProcess::ExitStatus status) {
	ApplicationFinishResult res;
	switch (status) {
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

void ApplicationWrapper::do_fin_hook(int exitCode, QProcess::ExitStatus status) {
	/* no matter what, process should be delete */
	appProcess->deleteLater();

	if (rawAppFinHook) {
		/* monitor the handling */
		rawAppFinHook(this, exitCode, status);
	} else {
		/* do the default then */
		mainWindow->show();
		ApplicationFinishResult r = create_from_raw(exitCode, status);
		emit app_finished(r);
	}
}

void ApplicationWrapper::def_error_handler() {
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
    ApplicationWrapper(QObject* parent, DesktopMainWindow* desktopWindow)
    : QObject(parent) {
    mainWindow = desktopWindow;
    pre_indicate = def_indicate;
}

void ApplicationWrapper::depatch_app() {
	/* we need to promise the app is exsited */
	if (pre_indicate) {
		ApplicationDepatchResult result = pre_indicate(this);
		emit app_depatch_status(result);
	}

	/* precheck is passed then */
	appProcess = new QProcess(this);
	connect(appProcess, &QProcess::finished,
			this, &ApplicationWrapper::do_fin_hook);

	/* hide the window for the new process start */
	mainWindow->hide();

	appProcess->start(app_path, app_args);
	/* slow spin */
	if (!appProcess->waitForStarted()) {
		if (error_handler) {
			error_handler(this);
		} else {
			def_error_handler();
		}
	}
}
