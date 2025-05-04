#include "homepage.h"
#include "ui_homepage.h"

HomePage::HomePage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::HomePage)
{
    ui->setupUi(this);
    ui->left_bottom_widget->bindClockWidget(ui->left_top_widget);
}

QWidget *HomePage::expected_appcards_widgets() const
{
    return ui->right_bottom_widget;
}

HomePage::~HomePage()
{
    delete ui;
}
