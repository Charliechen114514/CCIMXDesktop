#include "SportsDisplayWidget.h"
#include "ui_SportsDisplayWidget.h"

SportsDisplayWidget::SportsDisplayWidget(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::SportsDisplayWidget) {
	ui->setupUi(this);
}

SportsDisplayWidget::~SportsDisplayWidget() {
	delete ui;
}

void SportsDisplayWidget::setDisplay(const ICM20608AppData& data) {
	ui->label_g_x->setText("Rol x:" + QString::number(data.rol.x) + "/S");
	ui->label_g_y->setText("Rol y:" + QString::number(data.rol.y) + "/S");
	ui->label_g_z->setText("Rol z:" + QString::number(data.rol.z) + "/S");

	ui->label_a_x->setText("Acc x:" + QString::number(data.g_acc.x) + "g");
	ui->label_a_y->setText("Acc y:" + QString::number(data.g_acc.y) + "g");
	ui->label_a_z->setText("Acc z:" + QString::number(data.g_acc.z) + "g");

	ui->temp_label->setText(QString::number(data.temperature) + "degrees");
}
