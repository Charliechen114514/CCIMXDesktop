#include "AddPanel.h"
#include <QEvent>
#include <QIntValidator>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QRegularExpression>
#include <QVBoxLayout>
AddPanel::AddPanel(QWidget* parent)
    : QWidget(parent) {
    setWindowFlags(Qt::Popup | Qt::FramelessWindowHint);
    setFixedSize(240, 150);
    auto* lo = new QVBoxLayout(this);
    lo->setContentsMargins(12, 12, 12, 12);
    lo->setSpacing(8);

    QLabel* lbl = new QLabel("添加联系人", this);
    lbl->setStyleSheet("font-size:16px;font-weight:600;");
    lo->addWidget(lbl, 0, Qt::AlignCenter);

    editName = new QLineEdit(this);
    editName->setPlaceholderText("Name");
    lo->addWidget(editName);

    ipAddr = new QLineEdit(this);
    ipAddr->setPlaceholderText("127.0.0.1");
    QString ipRange = "(?:[0-1]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])";
    QRegularExpression ipRegex(
        "^" + ipRange + "\\." + ipRange + "\\." + ipRange + "\\." + ipRange + "$");
    auto* ipValidator = new QRegularExpressionValidator(ipRegex, this);
    ipAddr->setValidator(ipValidator);
    lo->addWidget(ipAddr);

    portAddr = new QLineEdit(this);
    auto* portValidator = new QIntValidator(1, 65535, this);
    portAddr->setValidator(portValidator);
    portAddr->setPlaceholderText("12345");
    lo->addWidget(portAddr);

    auto* btnOk = new QPushButton("Application", this);
    btnOk->setFixedHeight(32);
    lo->addWidget(btnOk);

    connect(btnOk, &QPushButton::clicked, this, [=]() {
        QString nm = editName->text().trimmed();

        if (!nm.isEmpty())
            emit addSubmitted(nm);

        int port = portAddr->text().toInt();
        QString ip_posible = ipAddr->text();
        QString ip = ip_posible.isEmpty() ? ipAddr->placeholderText() : ip_posible;
        emit request_new_connection(nm, ip, port);
        qDebug() << "Request add new connection on " << ip << " " << port;
    });

    setStyleSheet(R"(
            QWidget { background:#FFFFFF; border:1px solid #CCCCCC; border-radius:8px; }
            QPushButton { background:#0099FF; color:white; border:none; border-radius:4px; }
            QPushButton:hover { background:#007ACC; }
        )");
}

bool AddPanel::event(QEvent* ev) {
    if (ev->type() == QEvent::Close) {
        hide();
        return true;
    }
    return QWidget::event(ev);
}
