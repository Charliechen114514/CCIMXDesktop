#include "InterfacesDisplayWidget.h"
#include "core/interfaces_query/FormatDisplayFactory.h"
#include "core/interfaces_query/InterfacesQuery.h"
#include "ui/fasttools.h"
#include "ui_InterfacesDisplayWidget.h"
InterfacesDisplayWidget::InterfacesDisplayWidget(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::InterfacesDisplayWidget) {
	ui->setupUi(this);
	setup_memory();
	show_lists();
}

void InterfacesDisplayWidget::show_details() {
	hide_childrens(this);
	ui->btn_widgets->show();
	ui->details_tableWidget->show();
	ui->label->show();
}

void InterfacesDisplayWidget::show_lists() {
	hide_childrens(this);
	ui->interfaces_listwidget->show();
}

InterfacesDisplayWidget::~InterfacesDisplayWidget() {
	delete ui;
}

void InterfacesDisplayWidget::setup_memory() {
	query = new InterfacesQuery(this);
	connect(query, &InterfacesQuery::network_query_display,
			this, [this](const QStringList l) {
				ui->interfaces_listwidget->clear();
				ui->interfaces_listwidget->addItems(l);
			});

	connect(ui->interfaces_listwidget, &QListWidget::itemDoubleClicked,
			this, [this](QListWidgetItem* item) {
		auto result = query->from_name_query(item->text());
		if (result.has_value()) {
			install_interface_details(result.value());
			show_details();
		} else {
			qDebug() << "Can not check the details";
		} });

	connect(ui->details_tableWidget, &QTableWidget::itemClicked,
			this, [this](QTableWidgetItem* item) {
				ui->label->setText(item->text());
			});

	connect(ui->btn_goback, &QPushButton::clicked,
			this, &InterfacesDisplayWidget::show_lists);
}

void InterfacesDisplayWidget::
	install_interface_details(const QNetworkInterface& interfaces) {
	auto result = FormatDisplayFactory::details(interfaces);

	ui->details_tableWidget->setColumnCount(2);
	ui->details_tableWidget->setRowCount(result.count());
	int row = 0;
	for (const auto& res : std::as_const(result)) {
		ui->details_tableWidget->setItem(row, 0, new QTableWidgetItem(res.first));
		ui->details_tableWidget->setItem(row, 1, new QTableWidgetItem(res.second));
		row++;
	}
}
