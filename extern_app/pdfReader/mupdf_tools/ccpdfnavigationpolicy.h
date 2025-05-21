#ifndef CCPDFNAVIGATIONPOLICY_H
#define CCPDFNAVIGATIONPOLICY_H

#include "mupdf_adapter/ccpdfdocument.h"

/**
 * @class CCPdfNavigationPolicy
 * @brief Defines navigation behavior between PDF pages, especially in exceptional cases.
 *
 * This policy can be extended to define custom page flow rules and handle navigation exceptions.
 */
class CCPdfNavigationPolicy {
public:
	/**
	 * @brief Constructs a default CCPdfNavigationPolicy.
	 */
	CCPdfNavigationPolicy();

	/**
	 * @struct Indicator
	 * @brief Provides redirection information for navigation handling.
	 */
	struct Indicator {
		int new_page; ///< The page index to redirect to.
		bool req_follow_indicator; ///< Whether the redirection must be followed.
	};

	/**
	 * @typedef PdfBrowseExceptionFunctor
	 * @brief A function pointer type used to handle page navigation exceptions.
	 *
	 * This functor is called when an exception occurs during navigation.
	 *
	 * @param invoker The widget that initiated the navigation.
	 * @param invokee_document The document being navigated.
	 * @param error The specific navigation error encountered.
	 * @return An Indicator suggesting how to handle the navigation.
	 */
	using PdfBrowseExceptionFunctor = Indicator (*)(
		QWidget* invoker, ///< The widget that initiated the jump.
		CCPdfDocument* invokee_document, ///< The document under navigation.
		const CCPdfDocument::PageNavigationError ///< The navigation error encountered.
	);

	PdfBrowseExceptionFunctor page_navigate_functor; ///< Functor to handle page navigation exceptions.
};

#endif // CCPDFNAVIGATIONPOLICY_H
