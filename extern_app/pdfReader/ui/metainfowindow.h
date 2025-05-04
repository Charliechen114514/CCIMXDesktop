#ifndef METAINFOWINDOW_H
#define METAINFOWINDOW_H
#include "mupdf_tools/mupdf_tools.h"
#include <QMainWindow>

namespace Ui {
class MetaInfoWindow;
}

class MetaInfoWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MetaInfoWindow(QWidget *parent = nullptr);
    /* set the metas before you gonna display */
    void set_metas(const CCPdfMetaInfo& info);
    /* or if you wanna direct display, this is ur choice :) */
    void set_metas_and_display(const CCPdfMetaInfo& info);

    ~MetaInfoWindow();

private slots:
    void on_pushButton_clicked();

private:
    Ui::MetaInfoWindow *ui;
};

#endif // METAINFOWINDOW_H
