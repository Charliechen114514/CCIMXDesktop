#include "BonusFunctor.h"
#include "ui_BonusFunctor.h"
#include <QPushButton>

namespace {
QPushButton* standalone_button(const QString& name, QWidget* parent, QGridLayout* layout, int i, int j) {
    QPushButton* btn = new QPushButton(name, parent);
    btn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    layout->addWidget(btn, i, j);
    return btn;
}
}

BonusFunctor::BonusFunctor(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::BonusFunctor) {
	ui->setupUi(this);
    setup_panel();
}

BonusFunctor::~BonusFunctor() {
	delete ui;
}

void BonusFunctor::setup_panel() {
    // sin cos tan exp log sqrt DEL CLR
    static constexpr unsigned short WIDTH = 4;
    static constexpr unsigned short HEIGHT = 2;
    QString buttons[WIDTH][HEIGHT] = {
        { "sin", "cos" },
        { "tan", "exp" },
        { "log", "sqrt" },
        { "(", ")" }
    };

    QGridLayout* layout = dynamic_cast<QGridLayout*>(this->layout());
    for (int i = 0; i < WIDTH; i++) {
        for (int j = 0; j < HEIGHT; j++) {
            QPushButton* btn = new QPushButton(buttons[i][j], this);
            btn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            layout->addWidget(btn, i, j);
            connect(btn, &QPushButton::clicked, this, [this]() {
                QString send_m = qobject_cast<QPushButton*>(sender())->text();
                if (send_m != "(" && send_m != ")") {
                    send_m += "(";
                }
                emit req_append(send_m);
            });
        }
    }

    static constexpr unsigned short FUNC_WIDTH = 1;
    static constexpr unsigned short FUNC_HEIGHT = 2;
    QString functional_buttons[FUNC_WIDTH][FUNC_HEIGHT] = {
        { "CLR", "DEL" }
    };

    auto btn1 = standalone_button(functional_buttons[0][0], this, layout, 4, 0);
    connect(btn1, &QPushButton::clicked, this, &BonusFunctor::req_clear);

    auto btn2 = standalone_button(functional_buttons[0][1], this, layout, 4, 1);
    connect(btn2, &QPushButton::clicked, this, &BonusFunctor::req_chop_once);
}
