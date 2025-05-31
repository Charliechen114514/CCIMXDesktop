#include "DrawerWindow.h"

#include <QApplication>

int main(int argc, char* argv[]) {
	QApplication a(argc, argv);
	DrawerWindow w;
	w.show();
	return a.exec();
}
