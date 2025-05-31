#include "CCNoterWindow.h"
#include "./ui_CCNoterWindow.h"
#include "settings.h"
#include <QFileDialog>
#include <QFontDialog>
#include <QLabel>
#include <QSlider>
CCNoterWindow::CCNoterWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::CCNoterWindow) {
	ui->setupUi(this);
	setup_toolbars();
	init_connections();
}

void CCNoterWindow::load_file() {
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"));
	if (fileName.isEmpty()) {
		return;
	}
	QFile file(fileName);
	if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		QTextStream in(&file);
		ui->textEdit->setPlainText(in.readAll());
	}
}

void CCNoterWindow::save_file() {
	QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"));
	if (fileName.isEmpty()) {
		return;
	}
	QFile file(fileName);
	if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
		QTextStream out(&file);
		out << ui->textEdit->toPlainText();
	}
}

void CCNoterWindow::set_font_size(int size) {
	QTextCharFormat format;
	format.setFontPointSize(size);
	mergeFormatOnWordOrSelection(format);
}

void CCNoterWindow::chooseFont() {
	bool ok;
	QFont font = QFontDialog::getFont(&ok, ui->textEdit->font(), this);
	if (ok) {
		ui->textEdit->setFont(font);
	}
}

CCNoterWindow::~CCNoterWindow() {
	delete ui;
}

void CCNoterWindow::init_connections() {
	connect(ui->actionquit, &QAction::triggered,
			this, &CCNoterWindow::close);
	connect(ui->actionload, &QAction::triggered,
			this, &CCNoterWindow::load_file);
	connect(ui->actionsave, &QAction::triggered,
			this, &CCNoterWindow::save_file);
	connect(ui->actionfont, &QAction::triggered,
			this, &CCNoterWindow::chooseFont);
}

void CCNoterWindow::setup_toolbars() {
	QSlider* slider = new QSlider(this);
	slider->setMinimum(1);
	slider->setMaximum(40);
	slider->setValue(FONT_SZ);
	ui->toolBar->addWidget(slider);
	set_font_size(FONT_SZ);
	connect(slider, &QSlider::valueChanged,
			this, &CCNoterWindow::set_font_size);
	fontsize_label = new QLabel(this);
	fontstyle_label = new QLabel(this);
	fontsize_label->setText(QString("font size: %1 px ").arg(ui->textEdit->fontPointSize()));
	fontstyle_label->setText(QString("font family: " + ui->textEdit->fontInfo().styleName()));
	ui->toolBar->addWidget(fontsize_label);
	ui->toolBar->addWidget(fontstyle_label);
}

void CCNoterWindow::mergeFormatOnWordOrSelection(const QTextCharFormat& format) {
	QTextCursor cursor = ui->textEdit->textCursor();
	if (!cursor.hasSelection())
		cursor.select(QTextCursor::WordUnderCursor);
	cursor.mergeCharFormat(format);
	ui->textEdit->mergeCurrentCharFormat(format);
}

void CCNoterWindow::on_actionitalic_triggered(bool checked) {
	QTextCharFormat format;
	format.setFontItalic(checked);
	mergeFormatOnWordOrSelection(format);
}

void CCNoterWindow::on_actionbold_triggered(bool checked) {
	QTextCharFormat format;
	format.setFontWeight(checked ? QFont::Bold : QFont::Normal);
	mergeFormatOnWordOrSelection(format);
}
