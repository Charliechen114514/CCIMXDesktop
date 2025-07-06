#include "CalendarWindow.h"

#include <QApplication>

int main(int argc, char* argv[]) {
	QApplication a(argc, argv);
	CalendarWindow w;
	w.show();
	return a.exec();
}
