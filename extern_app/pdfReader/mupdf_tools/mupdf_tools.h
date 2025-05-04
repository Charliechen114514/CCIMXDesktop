#ifndef MUPDF_TOOLS_H
#define MUPDF_TOOLS_H
#include <QString>
#include <QVariant>
#include <QImage>
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

/* meta info packages */
struct CCPdfMetaInfo
{
    Q_GADGET
public:
    /* some fields */
    enum class Field
    {
        Author,
        Title,
        Subject,
        Keywords,
        Creator,
        Producer,
        CreationDateTime,
        ModifyDateTime
    };
    Q_ENUM(Field);

    QString         author;
    QString         title;
    QString         subject;
    QString         keywords;
    QString         creator;
    QString         producer;
    QString         creation_datetime;
    QString         modify_datetime;
};

struct CCPdfImageRequest {
    CCPdfDocument*      request_document;
    int                 request_page;
    float               zoom;
};

struct CCPdfChapterNode {
    QString                 chapter_title;
    int                     chapter_page;
    QList<CCPdfChapterNode> childs; /* childs of the current session */
};

/*
 *  at here, we gain the tools if one day we only query the submetas
 *
*/
namespace ccpdf_tools
{
/* request metas fulls*/
CCPdfMetaInfo
request_meta(const CCPdfDocument *document);

/* request metas seperates */
QVariant
request_target_meta(const CCPdfDocument* document,
                    const CCPdfMetaInfo::Field field);

/* request image, using by pdfview widget */
QImage
request_target_page(CCPdfImageRequest* simpleRequest);

QList<CCPdfChapterNode>
request_chapter_tree(const CCPdfDocument* document);

};

#endif // MUPDF_TOOLS_H
