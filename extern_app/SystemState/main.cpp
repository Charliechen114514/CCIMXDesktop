#include "SystemStateWindow.h"
#include <QApplication>

int main(int argc, char* argv[]) {
	QApplication a(argc, argv);
	SystemStateWindow w;
	w.show();
	return a.exec();
}
