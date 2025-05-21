#ifndef TOOLSSIDEBAR_H
#define TOOLSSIDEBAR_H
#include "mupdf_adapter/ccpdfchaptercreator.h"

#include <QWidget>
class CCPdfDocument;
namespace Ui {
class ToolsSideBar;
}

class ToolsSideBar : public QWidget {
	Q_OBJECT

public:
	explicit ToolsSideBar(QWidget* parent = nullptr);
	/**
	 * @brief set_document_chapterize this is using for document settings
	 * in the tools sidebars, the document is expected to be set with
	 * auto chapterize
	 * @param document_handling
	 */
	void set_document_chapterize(CCPdfDocument* document_handling);
	~ToolsSideBar();

signals:
	/**
	 * @brief sig_open_meta_info_window
	 * signal to open the meta info window
	 */
	void sig_open_meta_info_window();
	/**
	 * @brief sig_open_chapter_tree
	 * signal to open the chapter tree
	 */
	void required_page_jump(const int page);

private:
	CCPdfChapterCreator chapter_maker;
	Ui::ToolsSideBar* ui;
	void setup_connections();
};

#endif // TOOLSSIDEBAR_H
