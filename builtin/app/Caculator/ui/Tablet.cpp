#include "Tablet.h"
#include "core/ExpressionEvaluator.h"
#include "ui_Tablet.h"
#include <QPushButton>
Tablet::Tablet(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::Tablet) {
	ui->setupUi(this);
    setup_panel();
}

Tablet::~Tablet() {
	delete ui;
}

void Tablet::setResult(const QString& v) {
    string_expression = v;
    ui->lineEdit->setText(string_expression);
}

void Tablet::append_outlayer(const QString& what) {
    string_expression += what;
    ui->lineEdit->setText(string_expression);
}

void Tablet::process_clear() {
    string_expression.clear();
    ui->lineEdit->setText(string_expression);
}

void Tablet::process_chop() {
    if (!string_expression.isEmpty())
        string_expression.chop(1);
    ui->lineEdit->setText(string_expression);
}

void Tablet::process_evaluate() {
    // qDebug() << "Evaluating " << string_expression;
    try {
        double res = ExpressionEvaluator::evalute_expression(string_expression);
        string_expression = QString::number(res);
        ui->lineEdit->setText(string_expression);
    } catch (const std::runtime_error& e) {
        ui->lineEdit->setText(e.what());
    }
}

void Tablet::process_text_according() {
    QPushButton* btn = qobject_cast<QPushButton*>(sender());
    QString text = btn->text();

    if (text == "=") {
        process_evaluate();
    } else {
        append_outlayer(text);
    }
}

void Tablet::setup_panel() {
    static constexpr unsigned short WIDTH = 4;
    static constexpr unsigned short HEIGHT = 4;
    QString buttons[WIDTH][HEIGHT] = {
        { "7", "8", "9", "0" },
        { "4", "5", "6", "+" },
        { "1", "2", "3", "-" },
        { "/", "*", "^", "=" }
    };
    QGridLayout* layout = dynamic_cast<QGridLayout*>(ui->simple_tablet->layout());
    for (int i = 0; i < WIDTH; i++) {
        for (int j = 0; j < HEIGHT; j++) {
            QPushButton* btn = new QPushButton(buttons[i][j], this);
            btn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            layout->addWidget(btn, i, j);
            connect(btn, &QPushButton::clicked, this, &Tablet::process_text_according);
        }
    }
}
