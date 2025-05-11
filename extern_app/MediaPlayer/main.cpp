#include "ui/MediaPlayerWindow.h"
#include <QApplication>

int main(int argc, char* argv[]) {
	QApplication a(argc, argv);
	MediaPlayerWindow w;
	w.show();
	return a.exec();
}
