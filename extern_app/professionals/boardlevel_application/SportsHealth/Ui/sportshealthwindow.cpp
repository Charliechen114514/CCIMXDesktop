#include "sportshealthwindow.h"
#include "./ui_sportshealthwindow.h"
#include <QTimer>

SportsHealthWindow::SportsHealthWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::SportsHealthWindow) {
    ui->setupUi(this);
    /* test by using a timly request */
    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, ui->sports_chart,
            &SportsChart::flush_one_request);
    connect(ui->sports_chart, &SportsChart::fetch_once_data,
            ui->display_labels_widget, &SportsDisplayWidget::setDisplay);
    timer->start(1000);
}

SportsHealthWindow::~SportsHealthWindow() {
    delete ui;
}
