#include "sportshealthwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SportsHealthWindow w;
    w.show();
    return a.exec();
}
