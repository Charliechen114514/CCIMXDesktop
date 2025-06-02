#include "MainSideBar.h"
#include "LeftSideBar.h"
#include "ui_MainSideBar.h"
#include <QDesktopServices>
#include <QFileDialog>
#include <QInputDialog>
#include <QMessageBox>
MainSideBar::MainSideBar(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::MainSideBar) {
	ui->setupUi(this);
	ui->rawTextEditor->setPlaceholderText(DEF_PLACEHOLDER);
	run_init_example();
	connect(ui->rawTextEditor, &QPlainTextEdit::textChanged, this, &MainSideBar::process_once_fetch);
	connect(ui->makrdown_shower, &QTextBrowser::anchorClicked, this, [&](const QUrl& url) {
		QDesktopServices::openUrl(url);
	});
}

void MainSideBar::process_once_fetch() {
	QString mdText = ui->rawTextEditor->toPlainText();
	ui->makrdown_shower->setMarkdown(mdText);
}

void MainSideBar::load_file() {
	QString fileName = QFileDialog::getOpenFileName(this, "Open File", ".", "*.md");
	if (fileName.isEmpty()) {
		return;
	}
	commit_file(fileName);
}

void MainSideBar::request_cached() {
	QString label_name = QInputDialog::getText(this, "Label Name", "label_temp");
	auto labels = sidebar->temp_lables();
	if (labels.contains(label_name)) {
		QMessageBox::critical(this, "Duplicate label name", "Duplicate label name, switch a new one!");
		return;
	}
	sidebar->entemp(label_name, ui->rawTextEditor->toPlainText());
}

void MainSideBar::commit_file(const QString& fileName) {
	QFile file(fileName);
	if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		QTextStream in(&file);
		ui->rawTextEditor->setPlainText(in.readAll());
		from_already_cached = false;
		emit submit_enhist_request(fileName);
	} else {
		QMessageBox::critical(this, "Error", "Failed to open file: " + fileName + "Due to" + file.errorString());
	}
}

void MainSideBar::save_file() {
	QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), ".", "*.md");
	if (fileName.isEmpty()) {
		return;
	}
	QFile file(fileName);
	if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
		QTextStream out(&file);
		out << ui->rawTextEditor->toPlainText();
		emit submit_enhist_request(fileName);
	}
}

void MainSideBar::display_temperary(const QString& labels) {
	auto show = sidebar->show_temp(labels);
	if (show.has_value()) {
		from_already_cached = true;
		ui->rawTextEditor->setPlainText(show.value());
	} else {
		QMessageBox::critical(this, "Error", "Can not load temp from label: " + labels);
	}
}

MainSideBar::~MainSideBar() {
	delete ui;
}

void MainSideBar::run_init_example() {
	ui->rawTextEditor->setPlainText(
		"# Hello Qt Markdown\n\nInput **makes Bolder** or _UnderLine_ ...");
	process_once_fetch();
}

void MainSideBar::makeBold() {
	QTextCursor cursor = ui->rawTextEditor->textCursor();
	if (cursor.hasSelection()) {
		QString selectedText = cursor.selectedText();
		cursor.insertText("**" + selectedText + "**");
	} else {
		cursor.insertText("****");
		cursor.movePosition(QTextCursor::Left, QTextCursor::MoveAnchor, 2);
		ui->rawTextEditor->setTextCursor(cursor);
	}
}

void MainSideBar::makeItalic() {
	QTextCursor cursor = ui->rawTextEditor->textCursor();
	if (cursor.hasSelection()) {
		QString selectedText = cursor.selectedText();
		cursor.insertText("*" + selectedText + "*");
	} else {
		cursor.insertText("**");
		cursor.movePosition(QTextCursor::Left, QTextCursor::MoveAnchor, 1);
		ui->rawTextEditor->setTextCursor(cursor);
	}
}

void MainSideBar::makeUnderline() {
	QTextCursor cursor = ui->rawTextEditor->textCursor();
	if (cursor.hasSelection()) {
		QString selectedText = cursor.selectedText();
		cursor.insertText("_" + selectedText + "_");
	} else {
		cursor.insertText("__");
		cursor.movePosition(QTextCursor::Left, QTextCursor::MoveAnchor, 4);
		ui->rawTextEditor->setTextCursor(cursor);
	}
}
