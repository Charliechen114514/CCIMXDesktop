#include "DateNoter.h"
#include "DateDescriberFormatter.h"
#include "Noter.h"
#include "ui_DateNoter.h"
DateNoter::DateNoter(QWidget* parent)
    : PanelWidget(parent)
    , ui(new Ui::DateNoter) {
	ui->setupUi(this);
    connect(ui->btn_close, &QPushButton::clicked, this, [this]() {
        if (info) {
            const QString infos = ui->textBrowser->toPlainText();
            if (infos != info->notes) {
                info->notes = ui->textBrowser->toPlainText();
            }
        }

        slideOut();
    });

    ui->describeLabel->setText(DateDescriberFormatter::describeDate(current_date_handling));
}

DateNoter::~DateNoter() {
	delete ui;
}

void DateNoter::setDisplayingDate(const QDate& date, NoteInfo* info) {
    current_date_handling = date;
    ui->date_icon->setHandleDate(current_date_handling);
    if (info)
        ui->textBrowser->setText(info->notes);
    ui->describeLabel->setText(DateDescriberFormatter::describeDate(date));
}
