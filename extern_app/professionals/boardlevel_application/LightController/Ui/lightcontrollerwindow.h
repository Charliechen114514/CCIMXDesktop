#ifndef LIGHTCONTROLLERWINDOW_H
#define LIGHTCONTROLLERWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class LightControllerWindow;
}
QT_END_NAMESPACE

class LightControllerWindow : public QMainWindow
{
    Q_OBJECT

public:
    LightControllerWindow(QWidget *parent = nullptr);
    ~LightControllerWindow();

private:
    Ui::LightControllerWindow *ui;
};
#endif // LIGHTCONTROLLERWINDOW_H
