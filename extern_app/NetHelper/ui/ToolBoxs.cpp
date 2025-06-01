#include "ToolBoxs.h"
#include "ui_ToolBoxs.h"

ToolBoxs::ToolBoxs(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::ToolBoxs) {
	ui->setupUi(this);
	connect(ui->btn_show_interfaces, &QPushButton::clicked, this, [this]() {
		emit indicate_show(ShowType::INTERFACES);
	});

	connect(ui->btn_show_pinger, &QPushButton::clicked, this, [this]() {
		emit indicate_show(ShowType::PINGER);
	});

	connect(ui->btn_show_scanner, &QPushButton::clicked, this, [this]() {
		emit indicate_show(ShowType::SCANNER);
	});
}

ToolBoxs::~ToolBoxs() {
	delete ui;
}
