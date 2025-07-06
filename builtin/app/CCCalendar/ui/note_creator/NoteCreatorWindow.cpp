#include "NoteCreatorWindow.h"
#include "ui_NoteCreatorWindow.h"

NoteCreatorWindow::NoteCreatorWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::NoteCreatorWindow) {
	ui->setupUi(this);
}

NoteCreatorWindow::~NoteCreatorWindow() {
	delete ui;
}

void NoteCreatorWindow::setOperatingDate(const QDate& d) {
    ui->dateEdit->setDate(d);
}

void NoteCreatorWindow::on_buttonBox_accepted() {
    // qDebug() << "Accepted";
    this->hide();
    internal_package.color = ui->widget->color();
    internal_package.info = { ui->textBrowser->toPlainText() };
    internal_package.date = ui->dateEdit->date();
    emit accept_enqueue();
}

void NoteCreatorWindow::on_buttonBox_rejected() {
    // using in demo usage
    // qDebug() << "User Rejected the create notes selections"
}
