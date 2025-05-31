#ifndef MUPDF_TOOLS_H
#define MUPDF_TOOLS_H
#include <QImage>
#include <QString>
#include <QVariant>

/* 
 * MuPDF tools provide lightweight operations for PDF documents.
 * The following meta keys correspond to MuPDF's supported metadata:
 *
 * #define FZ_META_FORMAT "format"
 * #define FZ_META_ENCRYPTION "encryption"
 *
 * #define FZ_META_INFO "info:"
 * #define FZ_META_INFO_TITLE "info:Title"
 * #define FZ_META_INFO_AUTHOR "info:Author"
 * #define FZ_META_INFO_SUBJECT "info:Subject"
 * #define FZ_META_INFO_KEYWORDS "info:Keywords"
 * #define FZ_META_INFO_CREATOR "info:Creator"
 * #define FZ_META_INFO_PRODUCER "info:Producer"
 * #define FZ_META_INFO_CREATIONDATE "info:CreationDate"
 * #define FZ_META_INFO_MODIFICATIONDATE "info:ModDate"
 */

class CCPdfDocument;

/**
 * @brief CCPdfMetaInfo
 * Holds metadata extracted from a PDF document.
 */
struct CCPdfMetaInfo {
    Q_GADGET
public:
    /**
     * @brief Field
     * Enum representing available metadata fields.
     */
    enum class Field {
        Author, ///< The document's author.
        Title, ///< The document's title.
        Subject, ///< The document's subject.
        Keywords, ///< Keywords associated with the document.
        Creator, ///< Application that created the document.
        Producer, ///< PDF producing software.
        CreationDateTime, ///< Document creation datetime.
        ModifyDateTime ///< Last modification datetime.
    };
    /**
     * @brief enum object
     * 
     */
    Q_ENUM(Field);

    QString author; ///< The document's author.
    QString title; ///< The document's title.
    QString subject; ///< The document's subject.
    QString keywords; ///< Keywords for classification.
    QString creator; ///< Application that created the document.
    QString producer; ///< Software that produced the PDF.
    QString creation_datetime; ///< Creation date/time string.
    QString modify_datetime; ///< Modification date/time string.
};

/**
 * @brief CCPdfImageRequest
 * Request data structure for rendering a page as an image.
 */
struct CCPdfImageRequest {
    CCPdfDocument* request_document; ///< Pointer to the PDF document.
    int request_page; ///< Page index to render.
    float zoom; ///< Zoom factor for rendering.
};

/**
 * @brief CCPdfChapterNode
 * Represents a single node in the chapter/bookmark tree.
 */
struct CCPdfChapterNode {
    QString chapter_title; ///< Title of this chapter.
    int chapter_page; ///< Page number referred by this chapter.
    QList<CCPdfChapterNode> childs; ///< List of child chapter nodes.
};

/**
 * @namespace ccpdf_tools
 * Provides tools for extracting metadata and rendering content from PDF documents.
 */
namespace ccpdf_tools {

/**
 * @brief request_meta
 * Request all metadata from a PDF document.
 * @param document Pointer to the PDF document.
 * @return CCPdfMetaInfo structure with extracted metadata.
 */
CCPdfMetaInfo request_meta(const CCPdfDocument* document);

/**
 * @brief request_target_meta
 * Request a specific metadata field from the PDF document.
 * @param document Pointer to the PDF document.
 * @param field Metadata field to retrieve.
 * @return QVariant containing the requested metadata.
 */
QVariant request_target_meta(const CCPdfDocument* document,
                             const CCPdfMetaInfo::Field field);

/**
 * @brief request_target_page
 * Request a rendered image of a specific page.
 * @param simpleRequest Pointer to CCPdfImageRequest with render parameters.
 * @return QImage of the rendered page.
 */
QImage request_target_page(CCPdfImageRequest* simpleRequest);

/**
 * @brief request_chapter_tree
 * Request the chapter/bookmark tree of the PDF document.
 * @param document Pointer to the PDF document.
 * @return List of CCPdfChapterNode representing the chapter hierarchy.
 */
QList<CCPdfChapterNode> request_chapter_tree(const CCPdfDocument* document);

}

#endif // MUPDF_TOOLS_H
