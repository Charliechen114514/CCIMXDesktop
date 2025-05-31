#ifndef CCPDFCHAPTERCREATOR_H
#define CCPDFCHAPTERCREATOR_H
#include "mupdf_tools/mupdf_tools.h"
class QTreeWidget;
class QTreeWidgetItem;
class CCPdfDocument;

/**
 * @brief The CCPdfChapterCreator class
 * The CCPdfChapterCreator class provides the pdf chapter creator
 */
class CCPdfChapterCreator : public QObject {
    Q_OBJECT
public:
    /**
     * @brief Constructor, connects parse_start signal to parsing slot
     * @param parent optional parent QObject
     */
    explicit CCPdfChapterCreator(QObject* parent = nullptr)
        : QObject(parent) {
        connect(this, &CCPdfChapterCreator::parse_start,
                this, &CCPdfChapterCreator::process_parse);
    };

    /**
     * @brief bindSolvedTreeWidget
     * Bind the tree widget to the chapter creator
     * @param w the tree widget to be bound
     */
    void bindSolvedTreeWidget(QTreeWidget* w);

    /**
     * @brief parse_and_set
     * Parse the document and set the tree widget
     * @param parse_document the document to be parsed
     */
    void parse_and_set(CCPdfDocument* parse_document);

signals:
    /**
     * @brief parse_start
     * Signal emitted to start parsing
     * @param parse_document the document to be parsed
     */
    void parse_start(CCPdfDocument* parse_document);

    /**
     * @brief parse_finish
     * Signal emitted when parsing is finished
     * @param list the list of parsed chapter nodes
     */
    void parse_finish(QList<CCPdfChapterNode> list);

private:
    /**
     * @brief widget_handling
     * Pointer to the QTreeWidget bound for chapter display
     */
    QTreeWidget* widget_handling { nullptr };

    /**
     * @brief process_parse
     * Perform the actual parsing of the document
     * @param parse_document the document to parse
     */
    void process_parse(CCPdfDocument* parse_document);
};

#endif // CCPDFCHAPTERCREATOR_H
