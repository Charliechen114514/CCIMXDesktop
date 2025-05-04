#include <QHBoxLayout>
#include "downdockwidget.h"
#include <QGraphicsDropShadowEffect>
#include "ui_downdockwidget.h"
#include "appwidget.h"


DownDockWidget::DownDockWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::DownDockWidget)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_StyledBackground, true);
    setAutoFillBackground(true);
    setStyleSheet(
        "DownDockWidget {"
        "    background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, "
        "        stop:0 rgba(40, 40, 40, 0.8), stop:1 rgba(100, 100, 100, 0.8));"
        "    border-radius: 12px;"
        "    border: 1px solid rgba(100, 100, 100, 0.5);"
        "    padding: 16px;"
        "}"
        );

}

void DownDockWidget::set_dock_apps(const QList<AppWidget *> &apps)
{
    dock_apps = apps;
    replace_docks();
}

void DownDockWidget::replace_docks()
{
    for(const auto& each_app : std::as_const(dock_apps)){
        layout()->addWidget(each_app);
    }
}

DownDockWidget::~DownDockWidget()
{
    delete ui;
}


