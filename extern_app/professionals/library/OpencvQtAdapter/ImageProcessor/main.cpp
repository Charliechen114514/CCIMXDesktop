#include "ImageProcessorWindow.h"

#include <QApplication>

int main(int argc, char* argv[]) {
	QApplication a(argc, argv);
	ImageProcessorWindow w;
	w.show();
	return a.exec();
}
