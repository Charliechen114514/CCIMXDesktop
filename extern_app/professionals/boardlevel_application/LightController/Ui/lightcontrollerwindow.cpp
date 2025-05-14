#include "lightcontrollerwindow.h"
#include "./ui_lightcontrollerwindow.h"

LightControllerWindow::LightControllerWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LightControllerWindow)
{
    ui->setupUi(this);
}

LightControllerWindow::~LightControllerWindow()
{
    delete ui;
}
