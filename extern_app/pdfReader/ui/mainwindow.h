#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "mupdf_adapter/ccpdfdocument.h"
#include "mupdf_tools/ccpdfnavigationpolicy.h"
#include <QMainWindow>
class MetaInfoWindow;
class QLabel;
class CCPdfViewer;
class ToolsSideBar;
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

public slots:
    void open_documentFromDialog();
    void browse_document_metas();
    /* page navigations */
    void jump_to_page(const int page_index);
    void prev_page(void);
    void next_page(void);
    void switch_toolbox_state(void);
    void zoom_in(void);
    void zoom_out(void);
private:
    /* private Qt components */
    Ui::MainWindow *ui;
    QLabel*         page_navigation_indicator_label;
    /* subs of my components */
    std::unique_ptr<CCPdfDocument>  document_holders;
    std::shared_ptr<MetaInfoWindow> metainfo_window;
    CCPdfViewer*                    pdfdisplay_view;
    ToolsSideBar*                   tools_side_bar;
    CCPdfNavigationPolicy           policy;
    /* yeap my funtions */
    void    setup_connections();
    void    post_init_ui();
    /*  For embedded devices, we have to think carefully
        The performance issue :(, sadly
     */
    void    update_page_navigations_ui();
    /* This is a heavy invoke, that is, fresh the all components */
    void    update_ui_globally();
    void    init_once_pdfdoc(void);
};
#endif // MAINWINDOW_H
