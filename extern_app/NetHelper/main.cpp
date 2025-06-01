#include "NetMainWindow.h"

#include <QApplication>

int main(int argc, char* argv[]) {
	QApplication a(argc, argv);
	NetMainWindow w;
	w.show();
	return a.exec();
}
