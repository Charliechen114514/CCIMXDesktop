#include "ImageWalkerWindow.h"

#include <QApplication>

int main(int argc, char* argv[]) {
	QApplication a(argc, argv);
	ImageWalkerWindow w;
	w.show();
	return a.exec();
}
