#ifndef CCPDFDOCUMENT_H
#define CCPDFDOCUMENT_H

#include "mupdf_tools/mupdf_tools.h"
#include <QObject>
#include <optional>

/* 
 * Forward declarations related to MuPDF C API.
 * fz_context manages the global MuPDF context.
 * fz_document represents a loaded PDF document.
 */
struct fz_context;
struct fz_document;
struct CCPdfDocumentPrivate;

/**
 * @brief The CCPdfDocument class
 * CCPdfDocument manages the lifetime and access to a PDF document.
 * It encapsulates the underlying MuPDF C library resources.
 * This class is considered heavy-weight and should be used carefully
 * for performance-critical or lightweight PDF sessions.
 */
class CCPdfDocument : public QObject {
    Q_OBJECT
public:
    /**
     * @brief Default constructor.
     * @param parent Optional QObject parent.
     */
    explicit CCPdfDocument(QObject* parent = nullptr);

    /**
     * @brief Constructor that opens a document immediately.
     * @param document_path File path to the PDF document.
     */
    explicit CCPdfDocument(const QString& document_path);

    /**
     * @brief Destructor.
     * Releases resources associated with the document.
     */
    ~CCPdfDocument();
    /**
     * @brief disable copy object
     * 
     */
    Q_DISABLE_COPY(CCPdfDocument);

    /**
     * @brief ErrorCode
     * Enum describing possible error codes during document operations.
     */
    enum class ErrorCode {
        NO_ERROR,       ///< No error occurred.
        FILE_NOT_EXSIT, ///< File does not exist.
        OTHER_MISTAKES  ///< Other unspecified errors.
    };

    /**
     * @brief load_document
     * Loads a PDF document from the specified path.
     * @param document_path File path to load.
     * @return ErrorCode indicating success or failure reason.
     */
    ErrorCode load_document(const QString& document_path);

    /**
     * @brief close_document
     * Closes the currently loaded document.
     * @return True if the document was closed successfully.
     */
    bool close_document();

    /**
     * @brief document_loaded
     * Checks if a document is currently loaded.
     * @return True if loaded; false otherwise.
     */
    bool document_loaded() const;

    /**
     * @brief document_page
     * Gets the total number of pages in the loaded document.
     * @return Optional containing page count if loaded, or empty if none.
     */
    std::optional<uint32_t> document_page() const;

    /**
     * @brief raw_handle
     * Gets the raw pointer to the underlying MuPDF document.
     * @return Pointer to fz_document.
     */
    fz_document* raw_handle() const;

    /**
     * @brief raw_context
     * Gets the raw pointer to the MuPDF context.
     * @return Pointer to fz_context.
     */
    fz_context* raw_context() const;

    /**
     * @brief meta_info
     * Retrieves metadata information from the loaded document.
     * @return CCPdfMetaInfo structure with metadata.
     */
    CCPdfMetaInfo meta_info() const;

    /**
     * @brief current_page
     * Gets the current page index.
     * @note For GCC users, consider using __attribute__((always_inline))
     *       to force inline for performance as this may be called frequently.
     * @return Current page index.
     */
    inline int current_page() const { return current_page_index; }

    /**
     * @brief current_path
     * Gets the file path of the currently loaded document.
     * @return Current document file path.
     */
    inline QString current_path() const { return holding_path; }

    /**
     * @brief total_pages
     * Gets the total number of pages in the loaded document.
     * @return Total page count.
     */
    inline int total_pages() const { return total_page; }

    /**
     * @brief PageNavigationError
     * Enum representing errors when navigating pages.
     */
    enum class PageNavigationError {
        PAGE_OK,        ///< Navigation successful.
        PAGE_UNDERFLOW, ///< Page index below first page.
        PAGE_OVERFLOW,  ///< Page index beyond last page.
        PAGE_UNEXSITS   ///< Specified page does not exist.
    };

    /**
     * @brief jump
     * Attempts to jump to a specified page index.
     * @param page_index Target page index.
     * @return PageNavigationError indicating navigation result.
     */
    PageNavigationError jump(const int page_index);

signals:
    /**
     * @brief document_load
     * Signal emitted when a document is successfully loaded.
     * @param document_path The file path of the loaded document.
     */
    void document_load(const QString document_path);

    /**
     * @brief pageIndexChanged
     * Signal emitted when the current page index changes.
     * Used for lightweight UI updates or notifications.
     */
    void pageIndexChanged();

private:
    CCPdfDocumentPrivate* privated; ///< Pointer to private implementation.
    QString holding_path; ///< Current loaded document file path.
    int current_page_index { -1 }; ///< Current page index, -1 if none.
    int total_page { -1 }; ///< Total number of pages, -1 if none.
};

#endif // CCPDFDOCUMENT_H
