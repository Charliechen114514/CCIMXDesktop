#include "ccpdfdocument.h"
#include "mupdf_tools/mupdf_tools.h"
#include <QFile>
#include <mupdf/fitz.h>
/* oh that is because fz_context never a C++ Style struct */
struct CCPdfContextDeleter {
	void operator()(fz_context* ctx) const {
		if (ctx) {
			fz_drop_context(ctx);
		}
	}
};

struct CCPdfDocumentPrivate {
	Q_DISABLE_COPY(CCPdfDocumentPrivate);

	/* provide a base */
	CCPdfDocumentPrivate() {
		context = std::unique_ptr<fz_context, CCPdfContextDeleter>(
			fz_new_context(nullptr, nullptr, FZ_STORE_UNLIMITED));
		fz_register_document_handlers(context.get());
	}

	~CCPdfDocumentPrivate() {
		/* reach the time of erasing */
		if (document) {
			fz_drop_document(context.get(), document);
			document = nullptr;
		}
		/* as we have already define how to context */
		/* we actually do nothing here */
	}

	std::unique_ptr<fz_context, CCPdfContextDeleter> context;
	/*
	 * reason why I don't set this as unique_ptr is simple,
	 * erase of the fz_document is time-relevant, as I also need to
	 * design the front and back relationships of twos
	 * and that makes me feel sicks
	 */
	fz_document* document { nullptr };
};

CCPdfDocument::CCPdfDocument(QObject* parent)
	: QObject { parent } {
	/* init the privated */
	this->privated = new CCPdfDocumentPrivate;
}

CCPdfDocument::CCPdfDocument(const QString& document_path) {
	/* init the privated */
	this->privated = new CCPdfDocumentPrivate;
	/* load document direct */
	load_document(document_path);
}

bool CCPdfDocument::document_loaded() const {
	return privated->document != nullptr;
}

/* process the document loader */
CCPdfDocument::ErrorCode CCPdfDocument::load_document(const QString& document_path) {
	if (!QFile::exists(document_path)) {
		/* the file is not exsits, should check the path */
		return ErrorCode::FILE_NOT_EXSIT;
	}

	if (document_loaded()) {
		/* that means we need to change the holding handle */
		fz_drop_document(privated->context.get(), privated->document);
	}

	/* start our session then */
	privated->document = fz_open_document(
		privated->context.get(),
		document_path.toUtf8().data());
	current_page_index = 0;
	total_page = fz_count_pages(privated->context.get(), privated->document);
	/* broadcast the signals */
	emit document_load(document_path);
	/* means of the valid handler makes the correct sessions */
	return ErrorCode::NO_ERROR;
}

bool CCPdfDocument::close_document() {
	if (!document_loaded()) {
		return true;
	}

	fz_drop_document(privated->context.get(), privated->document);
	/* reset as the nullptr and values are set clear */
	privated->document = nullptr;
	current_page_index = -1;
	total_page = -1;
	return true;
}

std::optional<uint32_t> CCPdfDocument::document_page() const {
	/* that means the document is invalid */
	if (!document_loaded()) {
		return std::nullopt;
	}

	return total_page;
}

fz_document* CCPdfDocument::raw_handle() const {
	return privated->document;
}

fz_context* CCPdfDocument::raw_context() const {
	return privated->context.get();
}

CCPdfMetaInfo CCPdfDocument::meta_info() const {
	return ccpdf_tools::request_meta(this);
}

/* set the page for jump */
CCPdfDocument::PageNavigationError CCPdfDocument::jump(const int page_index) {
	if (total_page < 0) {
		return PageNavigationError::PAGE_UNEXSITS;
	}

	if (page_index >= total_page) {
		return PageNavigationError::PAGE_OVERFLOW;
	}

	if (page_index < 0) {
		return PageNavigationError::PAGE_UNDERFLOW;
	}
	/* yeah, set the page safely */
	current_page_index = page_index;

	/* and emit the signals now, it's safe */
	emit pageIndexChanged();

	return PageNavigationError::PAGE_OK;
}

CCPdfDocument::~CCPdfDocument() {
	delete privated;
}
