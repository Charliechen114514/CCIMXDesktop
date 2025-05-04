#include "metainfowindow.h"
#include "ui_metainfowindow.h"

MetaInfoWindow::MetaInfoWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MetaInfoWindow)
{
    ui->setupUi(this);
    static constexpr const char* PROPERTY_METAS[] = {
        "Title", "Author", "Subject", "Keywords",
        "Creator", "Producer", "Creation Date", "Modify Date"
    };

    static constexpr unsigned short PROPERTY_SZ =
        sizeof(PROPERTY_METAS) / sizeof(PROPERTY_METAS[0]);
    for(unsigned short i = 0; i < PROPERTY_SZ; i++){
        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(PROPERTY_METAS[i]));
    }
}

/* set the metas before you gonna display */
void MetaInfoWindow::set_metas(const CCPdfMetaInfo& info)
{
#define SET_METAS(offset, text) \
    ui->tableWidget->setItem(offset, 1, new QTableWidgetItem(text));

    SET_METAS(0, info.title);
    SET_METAS(1, info.author);
    SET_METAS(2, info.subject);
    SET_METAS(3, info.keywords);
    SET_METAS(4, info.creator);
    SET_METAS(5, info.producer);
    SET_METAS(6, info.creation_datetime);
    SET_METAS(7, info.modify_datetime);

/* dont let it overflow */
#undef SET_METAS
}
/* or if you wanna direct display, this is ur choice :) */
void MetaInfoWindow::set_metas_and_display(const CCPdfMetaInfo& info)
{
    set_metas(info);
    show();
}

MetaInfoWindow::~MetaInfoWindow()
{
    delete ui;
}

void MetaInfoWindow::on_pushButton_clicked()
{
    close();
}

