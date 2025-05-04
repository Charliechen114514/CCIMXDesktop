#ifndef CCPDFDOCUMENT_H
#define CCPDFDOCUMENT_H

#include <QObject>
#include "mupdf_tools/mupdf_tools.h"

/* announcement of the mupdf issues */
/*
 * fz_context helps holding a base context, however in C++
 * I make a decision in using C++ exception handler, so, this is
 * only using in mark the resources holder
 */
struct fz_context;
struct fz_document;
struct CCPdfDocumentPrivate;
/*
    CCPdfDocument is expected to hold a resources physically in
    Programming level, this is a heavy level of classes, for any
    easy and fast pdf sessions should be careful of using this class
*/
class CCPdfDocument : public QObject
{
    Q_OBJECT
public:
    explicit CCPdfDocument(QObject *parent = nullptr);
    /* direct open */
    explicit CCPdfDocument(const QString& document_path);
    /* move off sessions */
    ~CCPdfDocument();
    Q_DISABLE_COPY(CCPdfDocument);
    /* error codes here */
    enum class ErrorCode {
        NO_ERROR,
        FILE_NOT_EXSIT,
        OTHER_MISTAKES
    };

    /* document load */
    ErrorCode load_document(const QString& document_path);
    /* document close */
    bool close_document();
    /* see if the session is loaded */
    bool document_loaded() const;
    /* query interface of page count */
    std::optional<uint32_t> document_page() const;

    /* handler of row*/
    fz_document*                        raw_handle() const;
    fz_context*                         raw_context() const;
    /* meta infos */
    CCPdfMetaInfo                       meta_info() const;
    /*
     * For GNU C Lovers, if u worried the performace issue,
     * considering using __attribute__((always_inline))
     * attributes to push compilers using inline method to
     * reduce the cost, as this invokes frequently
     */
    inline int                          current_page() const{return current_page_index;}
    inline QString                      current_path() const{return holding_path;}
    inline int                          total_pages() const{return total_page;}
    enum class PageNavigationError{
        PAGE_OK,
        PAGE_UNDERFLOW,
        PAGE_OVERFLOW,
        PAGE_UNEXSITS
    };
    /* set the page for jump */
    PageNavigationError   jump(const int page_index);

signals:
    /* signals of document loadings */
    void document_load(const QString document_path);
    /* light weight page index changed */
    void pageIndexChanged();
private:
    CCPdfDocumentPrivate*                   privated;
    QString                                 holding_path;
    int                                     current_page_index{-1};
    int                                     total_page{-1};
};

#endif // CCPDFDOCUMENT_H
