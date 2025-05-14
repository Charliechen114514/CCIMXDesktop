#include "lightcontrollerwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LightControllerWindow w;
    w.show();
    return a.exec();
}
