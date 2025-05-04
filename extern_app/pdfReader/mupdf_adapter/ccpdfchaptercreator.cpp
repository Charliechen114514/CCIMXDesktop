#include "ccpdfchaptercreator.h"
#include "mupdf_tools/mupdf_tools.h"
#include <mupdf/fitz.h>
#include "ccpdfdocument.h"
#include <QTreeWidgetItem>
#include <QtConcurrent/QtConcurrent>
#include <QFuture>
#include <QFutureWatcher>
static void parse_tree(QTreeWidget* widget, QTreeWidgetItem* parent, const QList<CCPdfChapterNode>& nodes)
{
    for(const CCPdfChapterNode& each : nodes)
    {
        QTreeWidgetItem* item = new QTreeWidgetItem();
        item->setText(0, each.chapter_title);
        item->setData(0, Qt::UserRole, each.chapter_page);
        if(parent){
            parent->addChild(item);
        }else{
            widget->addTopLevelItem(item);
        }

        /* recursive handling */
        if(!each.childs.isEmpty())
            parse_tree(widget, item, each.childs);
    }
}

void CCPdfChapterCreator::bindSolvedTreeWidget(QTreeWidget *w)
{
    /* pass the tree widget and set this property */
    widget_handling = w;
    widget_handling->clear();
}


void CCPdfChapterCreator::parse_and_set(CCPdfDocument* parse_document)
{
    /* no widget handling, quit the issue */
    if(!widget_handling) return;
    /* I make a lazy decision, signal and slots can
     * process the async load automatically, in this case, deptach a signal
     * is much more easy then using QFuture / QFutureWatcher / QtConcurrent
    */
    emit parse_start(parse_document);
}

void CCPdfChapterCreator::process_parse(CCPdfDocument* parse_document){
    QList<CCPdfChapterNode> nodes = ccpdf_tools::request_chapter_tree(parse_document);
    widget_handling->clear();
    parse_tree(widget_handling, nullptr, nodes);
    widget_handling->resizeColumnToContents(0);
}
