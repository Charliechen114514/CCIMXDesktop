#include "ReadMeWidget.h"
#include "ui_ReadMeWidget.h"
#include <QFile>
ReadMeWidget::ReadMeWidget(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::ReadMeWidget) {
	ui->setupUi(this);
}

void ReadMeWidget::load_file(const QString& readme_path) {
	QFile f(readme_path);
	f.open(QIODevice::ReadOnly);
	if (f.isOpen()) {
		ui->textBrowser->setMarkdown(f.readAll());
	}
}

ReadMeWidget::~ReadMeWidget() {
	delete ui;
}
