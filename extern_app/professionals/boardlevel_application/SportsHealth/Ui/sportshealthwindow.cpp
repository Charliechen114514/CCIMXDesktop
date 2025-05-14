#include "sportshealthwindow.h"
#include "./ui_sportshealthwindow.h"

SportsHealthWindow::SportsHealthWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SportsHealthWindow)
{
    ui->setupUi(this);
}

SportsHealthWindow::~SportsHealthWindow()
{
    delete ui;
}
