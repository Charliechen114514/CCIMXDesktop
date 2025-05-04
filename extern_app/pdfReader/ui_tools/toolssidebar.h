#ifndef TOOLSSIDEBAR_H
#define TOOLSSIDEBAR_H
#include "mupdf_adapter/ccpdfchaptercreator.h"

#include <QWidget>
class CCPdfDocument;
namespace Ui {
class ToolsSideBar;
}

class ToolsSideBar : public QWidget
{
    Q_OBJECT

public:
    explicit ToolsSideBar(QWidget *parent = nullptr);
    void     set_document_chapterize(CCPdfDocument* document_handling);
    ~ToolsSideBar();

signals:
    void sig_open_meta_info_window();
    void required_page_jump(const int page);
private:
    CCPdfChapterCreator     chapter_maker;
    Ui::ToolsSideBar *ui;
    void setup_connections();
};

#endif // TOOLSSIDEBAR_H
