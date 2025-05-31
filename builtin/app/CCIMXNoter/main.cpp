#include "CCNoterWindow.h"

#include <QApplication>

int main(int argc, char* argv[]) {
	QApplication a(argc, argv);
	CCNoterWindow w;
	w.show();
	return a.exec();
}
