#include "CaculatorMainWindow.h"
#include "ui_CaculatorMainWindow.h"
#include <QKeyEvent>
CaculatorMainWindow::CaculatorMainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::CaculatorMainWindow) {
	ui->setupUi(this);
    connect(ui->bonusWidget, &BonusFunctor::req_append,
            ui->mainWidget, &Tablet::append_outlayer);
    connect(ui->bonusWidget, &BonusFunctor::req_chop_once,
            ui->mainWidget, &Tablet::process_chop);
    connect(ui->bonusWidget, &BonusFunctor::req_clear,
            ui->mainWidget, &Tablet::process_clear);
    connect(ui->actionExit, &QAction::triggered,
            this, &CaculatorMainWindow::close);
    this->setFocusPolicy(Qt::StrongFocus);
    this->setFocus();
}

CaculatorMainWindow::~CaculatorMainWindow() {
	delete ui;
}

void CaculatorMainWindow::keyPressEvent(QKeyEvent* event) {
    int key = event->key();
    if (key == Qt::Key_Backspace) {
        ui->mainWidget->process_chop();
    } else if (key == Qt::Key_Return || key == Qt::Key_Enter) {
        ui->mainWidget->process_evaluate();
    } else if (key == Qt::Key_Escape) {
        ui->mainWidget->process_clear();
    } else {
        QString ch = event->text();
        if (ch.length() == 1 && QString("0123456789+-*/^().").contains(ch)) {
            ui->mainWidget->append_outlayer(ch);
        }
    }
    QMainWindow::keyPressEvent(event);
}
