#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QLabel>
#include "ccpdfviewer.h"
#include "toolssidebar.h"
#include "ui_tools/uipagenavigationpolicy.h"
#include "mupdf_adapter/ccpdfdocument.h"
#include "metainfowindow.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    /* some dynamic post ui inits */
    post_init_ui();
    /* handling the connections setups */
    setup_connections();
}

void MainWindow::setup_connections()
{
    connect(ui->actionOpenDocument, &QAction::triggered, this, &MainWindow::open_documentFromDialog);
    connect(ui->actionQuit, &QAction::triggered, this, &MainWindow::close);
    connect(ui->actionprev_page, &QAction::triggered, this, &MainWindow::prev_page);
    connect(ui->actionnext_page, &QAction::triggered, this, &MainWindow::next_page);
    connect(ui->actionzoom_in, &QAction::triggered, this, &MainWindow::zoom_in);
    connect(ui->actionzoom_out, &QAction::triggered, this, &MainWindow::zoom_out);
    connect(ui->actionopen_toolbars, &QAction::triggered,
            this, &MainWindow::switch_toolbox_state);
}

void MainWindow::post_init_ui()
{
    /* init the sidebar */
    pdfdisplay_view = new CCPdfViewer(this);
    tools_side_bar = new ToolsSideBar(this);
    QWidgetList lmain;
    lmain << pdfdisplay_view;
    ui->sidebarWidget->addLayout(lmain,
                                 SideBarWidget::Role::MainSide);

    QWidgetList side_left;
    side_left << tools_side_bar;
    ui->sidebarWidget->addLayout(side_left,
                                 SideBarWidget::Role::SideBar);

    ui->sidebarWidget->setButtonVisible(false);
    ui->sidebarWidget->switch_state();
    /* init the page navigate indicator */
    page_navigation_indicator_label = new QLabel(this);
    statusBar()->addPermanentWidget(page_navigation_indicator_label);

    connect(tools_side_bar, &ToolsSideBar::sig_open_meta_info_window,
            this, &MainWindow::browse_document_metas);
    connect(tools_side_bar, &ToolsSideBar::required_page_jump, this,
            &MainWindow::jump_to_page);
}

void MainWindow::update_page_navigations_ui()
{
    if(!document_holders) return;
    /* this including the label update */
    int current_page = document_holders->current_page();
    int total_page = document_holders->total_pages();

    /* thus we provide a policy of display the labels */
    page_navigation_indicator_label->setText(
        UiPageNavigationPolicy::label_disp_indicator(
            current_page, total_page)
    );
}

/* This is a heavy invoke, that is, fresh the all components */
void    MainWindow::update_ui_globally()
{
    update_page_navigations_ui();
}

void MainWindow::open_documentFromDialog()
{
    /* init the holders until it really does */
    if(!document_holders){
        init_once_pdfdoc();
    }

    /* filename open from dialog selections */
    QString file = QFileDialog::getOpenFileName(this, "select", ".", "*.pdf");
    if(file.isEmpty()){
        return;
    }

    document_holders->load_document(file);
    pdfdisplay_view->bindDocument(document_holders.get());
    tools_side_bar->set_document_chapterize(document_holders.get());
    jump_to_page(0);
}

void MainWindow::jump_to_page(const int page_index)
{
    if(!document_holders) return;

    CCPdfDocument::PageNavigationError status =
        document_holders->jump(page_index);
    if(status == CCPdfDocument::PageNavigationError::PAGE_OK){
        /* the request is OK, so let the session ends! */
        update_page_navigations_ui();
        return;
    }
    /* else we must hold on the invalid sessions */
    CCPdfNavigationPolicy::Indicator
        indicator = policy.page_navigate_functor(this, document_holders.get(), status);
    if(indicator.req_follow_indicator){
        /* this means we need to invoke the jump again */
        jump_to_page(indicator.new_page);
    }
}

void MainWindow::prev_page(void)
{
    if(!document_holders) return;
    jump_to_page(document_holders->current_page() - 1);
}

void MainWindow::next_page(void)
{
    if(!document_holders) return;
    jump_to_page(document_holders->current_page() + 1);
}

void MainWindow::switch_toolbox_state(void)
{
    bool new_state = !ui->sidebarWidget->current_ui_states();
    ui->sidebarWidget->switch_state();
    const char* text_display = (new_state ? "Close ToolBox" : "Open ToolBox");
    ui->actionopen_toolbars->setText(text_display);
}

void MainWindow::zoom_in(void)
{
    pdfdisplay_view->fresh_zoom(
        CCPdfViewer::ZoomDirection::ZOOM_IN);
}

void MainWindow::zoom_out(void)
{
    pdfdisplay_view->fresh_zoom(
        CCPdfViewer::ZoomDirection::ZOOM_OUT);
}

void MainWindow::browse_document_metas()
{
    if(!document_holders){
        init_once_pdfdoc();
    }

    if(!document_holders->document_loaded()){
        QMessageBox::information(this, "Sorry!", "You haven't load the document!");
        return;
    }

    if(!metainfo_window){
        metainfo_window = std::make_shared<MetaInfoWindow>(this);
    }

    metainfo_window->set_metas_and_display(document_holders->meta_info());
}

void MainWindow::init_once_pdfdoc()
{
    document_holders = std::make_unique<CCPdfDocument>();
}


MainWindow::~MainWindow()
{
    delete ui;
}
