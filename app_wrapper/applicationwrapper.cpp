#include "applicationwrapper.h"
#include "desktopmainwindow.h"
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QProcess>
#include <QUuid>
void ApplicationWrapper::do_fin_hook(int exitCode, QProcess::ExitStatus status) {
	/* no matter what, process should be delete */
	appProcess->deleteLater();

	if (rawAppFinHook) {
		/* monitor the handling */
		rawAppFinHook(this, exitCode, status);
	} else {
		/* do the default then */
		mainWindow->show();
	}
}

void ApplicationWrapper::def_error_handler() {
	/* clean up everythings */
	appProcess->deleteLater();
	/* and went back the window */
	mainWindow->show();
}

ApplicationWrapper::
    ApplicationWrapper(QObject* parent, DesktopMainWindow* desktopWindow)
    : QObject(parent) {
    mainWindow = desktopWindow;
    internal_app_code = QUuid::createUuid().toString(QUuid::WithoutBraces);
}

void ApplicationWrapper::depatch_app() {
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
