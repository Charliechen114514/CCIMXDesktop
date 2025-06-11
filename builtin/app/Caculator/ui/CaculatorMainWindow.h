#ifndef CACULATORMAINWINDOW_H
#define CACULATORMAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class CaculatorMainWindow;
}
QT_END_NAMESPACE

class CaculatorMainWindow : public QMainWindow {
	Q_OBJECT

public:
    CaculatorMainWindow(QWidget* parent = nullptr);
	~CaculatorMainWindow();

protected:
    void keyPressEvent(QKeyEvent* event);

private:
    Ui::CaculatorMainWindow* ui;
};
#endif // CACULATORMAINWINDOW_H
