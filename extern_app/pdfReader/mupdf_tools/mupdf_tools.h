#ifndef MUPDF_TOOLS_H
#define MUPDF_TOOLS_H
#include <QImage>
#include <QString>
#include <QVariant>
/* mupdf tools are expected to make some light wighted operations */
class CCPdfDocument;

/*
    The MuPdf Supports this infos, so make this be

#define FZ_META_FORMAT "format"
#define FZ_META_ENCRYPTION "encryption"

#define FZ_META_INFO "info:"
#define FZ_META_INFO_TITLE "info:Title"
#define FZ_META_INFO_AUTHOR "info:Author"
#define FZ_META_INFO_SUBJECT "info:Subject"
#define FZ_META_INFO_KEYWORDS "info:Keywords"
#define FZ_META_INFO_CREATOR "info:Creator"
#define FZ_META_INFO_PRODUCER "info:Producer"
#define FZ_META_INFO_CREATIONDATE "info:CreationDate"
#define FZ_META_INFO_MODIFICATIONDATE "info:ModDate"
*/

/// Meta information package extracted from a PDF document.
struct CCPdfMetaInfo {
	Q_GADGET
public:
	/// Enum of metadata fields available from the document.
	enum class Field {
		Author, ///< The document's author.
		Title, ///< The document's title.
		Subject, ///< The subject of the document.
		Keywords, ///< Keywords associated with the document.
		Creator, ///< The application that created the document.
		Producer, ///< The PDF producer.
		CreationDateTime, ///< The creation date and time.
		ModifyDateTime ///< The last modification date and time.
	};
	Q_ENUM(Field);

	QString author; ///< The document's author.
	QString title; ///< The document's title.
	QString subject; ///< The subject of the document.
	QString keywords; ///< Keywords for document classification.
	QString creator; ///< The application that created the document.
	QString producer; ///< The software that produced the PDF.
	QString creation_datetime; ///< Document creation date and time in string format.
	QString modify_datetime; ///< Last modification date and time in string format.
};

/// Request structure for rendering a specific page as an image.
struct CCPdfImageRequest {
	CCPdfDocument* request_document; ///< Pointer to the document to render.
	int request_page; ///< Page index to render.
	float zoom; ///< Zoom factor for rendering.
};

/// A single node in the chapter (bookmark) hierarchy.
struct CCPdfChapterNode {
	QString chapter_title; ///< Title of the chapter.
	int chapter_page; ///< Page number this chapter refers to.
	QList<CCPdfChapterNode> childs; ///< Children of the current chapter node.
};

/// Tools to extract metadata and render content from PDF documents.
namespace ccpdf_tools {
/**
 * @brief Requests the full set of metadata from a PDF document.
 * @param document Pointer to the document to query.
 * @return A CCPdfMetaInfo object with all available metadata.
 */
CCPdfMetaInfo
request_meta(const CCPdfDocument* document);

/**
 * @brief Requests a single piece of metadata from the PDF document.
 * @param document Pointer to the document to query.
 * @param field The specific field to retrieve.
 * @return A QVariant containing the requested metadata field.
 */
QVariant
request_target_meta(const CCPdfDocument* document,
                    const CCPdfMetaInfo::Field field);

/**
 * @brief Requests a rendered image of a specific page.
 * @param simpleRequest Pointer to the request containing document, page, and zoom level.
 * @return A QImage of the rendered page.
 */
QImage
request_target_page(CCPdfImageRequest* simpleRequest);

/**
 * @brief Requests the chapter tree (e.g., bookmarks) of the document.
 * @param document Pointer to the document to query.
 * @return A list of CCPdfChapterNode representing the chapter hierarchy.
 */
QList<CCPdfChapterNode>
request_chapter_tree(const CCPdfDocument* document);
};

#endif // MUPDF_TOOLS_H
