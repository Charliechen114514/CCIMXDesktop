#include "DinasourGameWindow.h"

#include <QApplication>

int main(int argc, char* argv[]) {
	QApplication a(argc, argv);
	DinasourGameWindow w;
	w.show();
	return a.exec();
}
