#ifndef ENVIRONMENTWINDOW_H
#define ENVIRONMENTWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class EnvironmentWindow;
}
QT_END_NAMESPACE

class EnvironmentWindow : public QMainWindow
{
    Q_OBJECT

public:
    EnvironmentWindow(QWidget *parent = nullptr);
    ~EnvironmentWindow();

private:
    Ui::EnvironmentWindow *ui;
};
#endif // ENVIRONMENTWINDOW_H
