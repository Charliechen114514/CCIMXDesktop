#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

/**
 * @brief MainWindow for example show
 * 
 */
class MainWindow : public QMainWindow {
	Q_OBJECT

public:
	/**
	 * @brief Construct a new Main Window object
	 * 
	 * @param parent 
	 */
	MainWindow(QWidget* parent = nullptr);
	~MainWindow();

private:
	Ui::MainWindow* ui;
};
#endif // MAINWINDOW_H
