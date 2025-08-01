#include "desktopmainwindow.h"
#include "ui/splash_window/CCIMX_DesktopSplashWindow.h"
#include <QApplication>

int main(int argc, char* argv[]) {
	QApplication a(argc, argv);
	/* this is the main entry mainwindow */
	DesktopMainWindow w;
    CCIMX_DesktopSplashWindow splash_window;
    splash_window.show();
    a.processEvents();
    w.init(&splash_window);
    /* init the window sessions */
    splash_window.close();
    w.show();
    w.post_show();
	/* then emit the post settings */
	return a.exec();
}
