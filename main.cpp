#include "desktopmainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    /* this is the main entry mainwindow */
    DesktopMainWindow w;
    w.show();
    /* then emit the post settings */
    w.post_inits();
    return a.exec();
}
