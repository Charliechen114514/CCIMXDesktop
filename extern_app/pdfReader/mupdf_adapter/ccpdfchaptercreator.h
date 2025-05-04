#ifndef CCPDFCHAPTERCREATOR_H
#define CCPDFCHAPTERCREATOR_H
#include "mupdf_tools/mupdf_tools.h"
class QTreeWidget;
class QTreeWidgetItem;
class CCPdfDocument;

class CCPdfChapterCreator : public QObject
{
    Q_OBJECT
public:
    explicit CCPdfChapterCreator(QObject* parent = nullptr) : QObject(parent){
        connect(this, &CCPdfChapterCreator::parse_start,
                this, &CCPdfChapterCreator::process_parse);
    };

    void bindSolvedTreeWidget(QTreeWidget* w);
    void parse_and_set(CCPdfDocument* parse_document);
signals:
    void parse_start(CCPdfDocument* parse_document);
    void parse_finish(QList<CCPdfChapterNode>);

private:
    QTreeWidget*        widget_handling{nullptr};
    void process_parse(CCPdfDocument* parse_document);
};

#endif // CCPDFCHAPTERCREATOR_H
