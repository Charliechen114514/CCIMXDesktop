#include <QScrollArea>
#include <QPainter>
#include <QLabel>
#include "ccpdfscrollarea.h"
#include "ccpdfviewer.h"
#include "mupdf_tools/mupdf_tools.h"
#include "ui_ccpdfviewer.h"
#include "ccpdfdocument.h"

CCPdfViewer::CCPdfViewer(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CCPdfViewer)
{
    ui->setupUi(this);
    init_internal();
}

void CCPdfViewer::init_internal()
{
    imageLabel = new QLabel;
    imageLabel->setAlignment(Qt::AlignTop | Qt::AlignHCenter);
    ui->scrollArea->setAlignment(Qt::AlignHCenter | Qt::AlignTop);
    ui->scrollArea->setWidget(imageLabel);
}

bool CCPdfViewer::bindDocument(CCPdfDocument* bindDocument)
{
    if(!bindDocument->document_loaded()){
        return false;   /* unloaded document */
    }

    /* now bind the document */
    document_for_view = bindDocument;
    connect(document_for_view, &CCPdfDocument::pageIndexChanged,
            this, &CCPdfViewer::fresh_render);

    return true;
}

void CCPdfViewer::unbindDocument(){
    /* if there is no document, then returns directly */
    if(!document_for_view) return;
    /* else we owns the issue, quit then */
    disconnect(document_for_view, &CCPdfDocument::pageIndexChanged,
            this, &CCPdfViewer::fresh_render);
}

/* calling this makes an update */
void CCPdfViewer::fresh_render()
{
    if(!document_for_view) return;
    /* query the image right now */
    CCPdfImageRequest   request {
        document_for_view,
        document_for_view->current_page(),
        view_zoom
    };
    /* make a request and fetch the page */
    cached_image = ccpdf_tools::request_target_page(&request);
    imageLabel->setPixmap(QPixmap::fromImage(cached_image));
    imageLabel->resize(cached_image.size());
}


CCPdfViewer::~CCPdfViewer()
{
    delete ui;
}
