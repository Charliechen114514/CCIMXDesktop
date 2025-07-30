#include "CommunicateMainWindow.h"

#include <QApplication>

int main(int argc, char* argv[]) {
	QApplication a(argc, argv);
	CommunicateMainWindow w;
	w.show();
	return a.exec();
}
