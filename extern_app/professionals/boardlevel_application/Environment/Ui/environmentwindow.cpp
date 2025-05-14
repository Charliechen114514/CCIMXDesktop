#include "environmentwindow.h"
#include "./ui_environmentwindow.h"

EnvironmentWindow::EnvironmentWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::EnvironmentWindow)
{
    ui->setupUi(this);
}

EnvironmentWindow::~EnvironmentWindow()
{
    delete ui;
}
