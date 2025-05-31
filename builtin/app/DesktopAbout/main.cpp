#include "AboutMainWindow.h"

#include <QApplication>

int main(int argc, char* argv[]) {
	QApplication a(argc, argv);
	AboutMainWindow w;
	w.show();
	return a.exec();
}
