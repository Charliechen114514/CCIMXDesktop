#include "CaculatorMainWindow.h"

#include <QApplication>

int main(int argc, char* argv[]) {
	QApplication a(argc, argv);
	CaculatorMainWindow w;
	w.show();
	return a.exec();
}
