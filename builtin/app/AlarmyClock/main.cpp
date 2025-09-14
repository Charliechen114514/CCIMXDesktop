#include "clockwindow.h"
#include <QApplication>

int main(int argc, char* argv[]) {
	QApplication a(argc, argv);
	ClockWindow w;
	w.show();
	return a.exec();
}
