#ifndef CCPDFNAVIGATIONPOLICY_H
#define CCPDFNAVIGATIONPOLICY_H
#include "mupdf_adapter/ccpdfdocument.h"


/*
 *  Navigation Policy is expected, at least, provide the
 *  page flows policy when jump in between pages and pages
 *  At current version, it is expected to handle the exception
 *  cases, who else know what will it be in next :)
 */
class CCPdfNavigationPolicy
{
public:
    CCPdfNavigationPolicy();

    struct Indicator {
        /* yeah, the indicator suggests the redirect pages */
        int     new_page;
        /*  whether the indications is a kind of must*/
        bool    req_follow_indicator;
    };

    /*
     * you should register the indications of some exceptions
     */
    using PdfBrowseExceptionFunctor = Indicator(*)(
        /* Who else involk the jump? */
        QWidget* invoker,
        /* What document is involker handling? */
        CCPdfDocument*  invokee_document,
        /* At what status should be handled? */
        const CCPdfDocument::PageNavigationError);
    PdfBrowseExceptionFunctor page_navigate_functor;
};

#endif // CCPDFNAVIGATIONPOLICY_H
