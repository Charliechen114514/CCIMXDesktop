#include "timercreatorwindow.h"
#include "alarmynote.h"
#include "edittimewidget.h"
#include <QHBoxLayout>
#include <QTextEdit>
#include <QPushButton>

TimerCreatorWindow::TimerCreatorWindow(QWidget* parent)
    : QMainWindow { parent } {
    QWidget* central_widget = new QWidget(this);
    QHBoxLayout* layout = new QHBoxLayout(this);
    central_widget->setLayout(layout);
    setCentralWidget(central_widget);

    EditTimeWidget* timeEditor = new EditTimeWidget(this);
    layout->addWidget(timeEditor);
    QTextEdit* textEdit = new QTextEdit(this);
    layout->addWidget(textEdit);

    QVBoxLayout* buttonsLayout = new QVBoxLayout(this);
    QPushButton* ok_button = new QPushButton(this);
    ok_button->setText("Submit");
    QPushButton* cancle_button = new QPushButton(this);
    cancle_button->setText("Quit");
    buttonsLayout->addWidget(ok_button);
    buttonsLayout->addWidget(cancle_button);
    layout->addLayout(buttonsLayout);

    connect(ok_button, &QPushButton::clicked, this, [this, textEdit, timeEditor](){
        // Ok notify this
        qDebug() << "Submit a new Timer Here!";
        emit notifyNewTimer(new AlarmyNote({
            timeEditor->time().hour(),
            timeEditor->time().minute(),0
        }, textEdit->toPlainText()));
        this->hide();
    });

    connect(cancle_button, &QPushButton::clicked, this, &TimerCreatorWindow::hide);
}
