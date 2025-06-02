#include "EasyNoteMainWindow.h"

#include <QApplication>

int main(int argc, char* argv[]) {
	QApplication a(argc, argv);
	EasyNoteMainWindow w;
	w.show();
	return a.exec();
}
