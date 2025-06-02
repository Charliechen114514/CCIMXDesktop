#include "LeftSideBar.h"
#include "core/TemperaryCacher.h"
#include "ui_LeftSideBar.h"
LeftSideBar::LeftSideBar(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::LeftSideBar) {
	ui->setupUi(this);
	cacher = new TemperaryCacher;
	init_connections();
}

LeftSideBar::~LeftSideBar() {
	delete cacher;
	delete ui;
}

QStringList LeftSideBar::temp_lables() const {
	return cacher->labels();
}

void LeftSideBar::enqueue_history_file(const QString& file) {
	history_file.removeAll(file);
	history_file.prepend(file);
	updateHistoryList();
}

void LeftSideBar::entemp(const QString& label, const QString& context) {
	cacher->ensub_labels(label, context);
	update_templist();
}

void LeftSideBar::remove_temp(const QString& label) {
	cacher->remove_label(label);
	update_templist();
}

std::optional<QString> LeftSideBar::show_temp(const QString& label) {
	return cacher->query(label);
}

void LeftSideBar::updateHistoryList() {
	ui->history_widget->clear();
	ui->history_widget->addItems(history_file);
}

void LeftSideBar::init_connections() {
	connect(ui->temp_list, &QListWidget::itemDoubleClicked,
			this, [this](QListWidgetItem* item) {
				emit load_temp(item->text());
			});
	connect(ui->history_widget, &QListWidget::itemDoubleClicked,
			this, [this](QListWidgetItem* item) {
				emit load_file(item->text());
			});
}

void LeftSideBar::update_templist() {
	ui->temp_list->clear();
	ui->temp_list->addItems(cacher->labels());
}

void LeftSideBar::on_btn_clear_temp_clicked() {
	ui->temp_list->clear();
	cacher->clear();
}

void LeftSideBar::on_btn_delete_clicked() {
	auto items = ui->temp_list->selectedItems();
	if (items.empty()) {
		return;
	}
	for (const auto& item : std::as_const(items)) {
		remove_temp(item->text());
	}
}
