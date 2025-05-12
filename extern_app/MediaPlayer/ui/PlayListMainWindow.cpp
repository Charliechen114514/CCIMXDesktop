#include "PlayListMainWindow.h"
#include "ui_PlayListMainWindow.h"
#include <QCloseEvent>
#include <QMessageBox>
PlayListMainWindow::PlayListMainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::PlayListMainWindow) {
	ui->setupUi(this);
	ui->btn_delete->hide();
	connect(ui->btn_cancle_delete, &QPushButton::clicked,
			this, &PlayListMainWindow::flip_edit_mode);
	connect(ui->btn_delete, &QPushButton::clicked,
			this, &PlayListMainWindow::process_select_delete);
	connect(ui->btn_exit, &QPushButton::clicked,
			this, [this]() {
				if (in_edit_mode) {
					flip_edit_mode();
				}
				close();
			});
	connect(ui->listWidget, &QListWidget::itemDoubleClicked, this,
			&PlayListMainWindow::process_item_click);
}

void PlayListMainWindow::flip_edit_mode() {
	in_edit_mode = !in_edit_mode;
	if (in_edit_mode) {
		ui->btn_delete->show();
		ui->btn_cancle_delete->setText("Cancel");
	} else {
		ui->btn_delete->hide();
		ui->btn_cancle_delete->setText("Edit");
	}
}

PlayListMainWindow::~PlayListMainWindow() {
	delete ui;
}

void PlayListMainWindow::from_media_list(const QStringList& l) {
	ui->listWidget->clear();
	ui->listWidget->addItems(l);
}

void PlayListMainWindow::process_select_delete() {
	QListWidgetItem* item = ui->listWidget->currentItem();
	if (!item) {
		QMessageBox::information(this, "inform", "You should select a media to delete");
		return;
	}

	emit delete_media(item->text());
	delete ui->listWidget->takeItem(ui->listWidget->row(item));
}

void PlayListMainWindow::process_item_click() {
	if (!in_edit_mode) {
		emit refresh_media_list();
		emit play_media(ui->listWidget->currentItem()->text());
	} else {
		ui->listWidget->setCurrentItem(ui->listWidget->currentItem());
	}
}
