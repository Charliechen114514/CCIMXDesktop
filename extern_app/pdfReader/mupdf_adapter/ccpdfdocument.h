#ifndef CCPDFDOCUMENT_H
#define CCPDFDOCUMENT_H

#include "mupdf_tools/mupdf_tools.h"
#include <QObject>

/* announcement of the mupdf issues */
/*
 * fz_context helps holding a base context, however in C++
 * I make a decision in using C++ exception handler, so, this is
 * only using in mark the resources holder
 */
struct fz_context;
struct fz_document;
struct CCPdfDocumentPrivate;
/**
 * @brief The CCPdfDocument class
 *  CCPdfDocument is expected to hold a resources physically in
 *  Programming level, this is a heavy level of classes, for any
 *  easy and fast pdf sessions should be careful of using this class
 */
class CCPdfDocument : public QObject {
	Q_OBJECT
public:
	explicit CCPdfDocument(QObject* parent = nullptr);
	/* direct open */
	explicit CCPdfDocument(const QString& document_path);
	/* move off sessions */
	~CCPdfDocument();
	Q_DISABLE_COPY(CCPdfDocument);

	/**
	 * @brief The ErrorCode enum
	 * The ErrorCode enum provides the error code
	 */
	enum class ErrorCode {
		NO_ERROR, ///< no error
		FILE_NOT_EXSIT, ///< file not exists
		OTHER_MISTAKES ///< other mistakes
	};

	/**
	 * @brief load_document load the document by the path given
	 * @param document_path the path of the document
	 * @return the error code of open sessions
	 */
	ErrorCode load_document(const QString& document_path);

	/**
	 * @brief close_document close the document
	 * @return true if the document is closed successfully
	 */
	bool close_document();

	/**
	 * @brief document_loaded check if the document is loaded
	 * @return true if the document is loaded
	 */
	bool document_loaded() const;

	/**
	 * @brief document_page get the page count of the document
	 * @return the page count of the document
	 */
	std::optional<uint32_t> document_page() const;

	/**
	 * @brief raw_handle
	 * @return fz_document as raw handle
	 */
	fz_document* raw_handle() const;

	/**
	 * @brief raw_context
	 * @return
	 */
	fz_context* raw_context() const;

	/**
	 * @brief meta_info
	 * @return
	 */
	CCPdfMetaInfo meta_info() const;
	/**
	 * @brief current pages in documentations
	 * @note For GNU C Lovers, if u worried the performace issue,
	 * considering using __attribute__((always_inline))
	 * attributes to push compilers using inline method to
	 * reduce the cost, as this invokes frequently
	 */
	inline int current_page() const { return current_page_index; }

	/**
	 * @brief current_path current holding paths
	 * @return current_path handlings
	 */
	inline QString current_path() const { return holding_path; }

	/**
	 * @brief total_pages total pages the doc has
	 * @return total_pages
	 */
	inline int total_pages() const { return total_page; }
	/**
	 * @enum PageNavigationError
	 * @brief Represents possible errors that can occur during page navigation.
	 */
	enum class PageNavigationError {
		PAGE_OK, /**< Navigation succeeded without error. */
		PAGE_UNDERFLOW, /**< Attempted to navigate to a page before the first page. */
		PAGE_OVERFLOW, /**< Attempted to navigate to a page beyond the last page. */
		PAGE_UNEXSITS /**< The specified page does not exist. */
	};

	/**
	 * @brief Jumps to the specified page index.
	 *
	 * This function attempts to change the current page to the given index.
	 *
	 * @param page_index The index of the page to jump to.
	 * @return PageNavigationError Returns the result of the navigation attempt.
	 */
	PageNavigationError jump(const int page_index);

signals:
	/**
	 * @brief Emitted when a document is loaded.
	 *
	 * @param document_path The file path of the loaded document.
	 */
	void document_load(const QString document_path);

	/**
	 * @brief Emitted when the current page index changes.
	 *
	 * This signal is used for lightweight notifications when the page index is updated.
	 */
	void pageIndexChanged();

private:
	CCPdfDocumentPrivate* privated;
	QString holding_path; ///< holding path now
	int current_page_index { -1 }; ///< page index now
	int total_page { -1 }; ///< total pages holding
};

#endif // CCPDFDOCUMENT_H
