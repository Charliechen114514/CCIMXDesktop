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
	explicit CCPdfChapterCreator(QObject* parent = nullptr)
		: QObject(parent) {
		connect(this, &CCPdfChapterCreator::parse_start,
				this, &CCPdfChapterCreator::process_parse);
	};

	/**
	 * @brief bindSolvedTreeWidget
	 * bind the tree widget to the chapter creator
	 * @param w the tree widget to be bound
	 */
	void bindSolvedTreeWidget(QTreeWidget* w);
	/**
	 * @brief parse_and_set parse the document and set the tree widget
	 * @param parse_document the document to be parsed
	 */
	void parse_and_set(CCPdfDocument* parse_document);
signals:
	/**
	 * @brief parse_start the signal to start parsing
	 * @param parse_document the document to be parsed
	 */
	void parse_start(CCPdfDocument* parse_document);

	/**
	 * @brief parse_finish the signal to finish parsing
	 */
	void parse_finish(QList<CCPdfChapterNode>);

private:
	QTreeWidget* widget_handling { nullptr };
	/**
	 * @brief process_parse process the parse actually
	 * @param parse_document
	 */
	void process_parse(CCPdfDocument* parse_document);
};

#endif // CCPDFCHAPTERCREATOR_H
