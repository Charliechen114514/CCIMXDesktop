#include "ccpdfnavigationpolicy.h"
#include <QMessageBox>
/*  default indications
 *  For compiling time redefined behavior, you can modified
 *  this for your project :)
 *  ELSE, if you are not, trying to modify the behaviour in
 *  runtime, you should really using runtime registritions!
 */
static CCPdfNavigationPolicy::Indicator def_indicate(
    QWidget*            invoker,
    CCPdfDocument*      invokee_document,
    const CCPdfDocument::PageNavigationError error
){
    CCPdfNavigationPolicy::Indicator indicator;
    switch(error){
        case CCPdfDocument::PageNavigationError::PAGE_OK:
            /* the page navigations is OK, so why fucking handles? */
        break;
        case CCPdfDocument::PageNavigationError::PAGE_OVERFLOW:
            /* as expected, we can backroll to the page 0 */
            indicator.new_page = 0;
            /* defaultly, we expected for the page redirect */
            indicator.req_follow_indicator = true;
        break;
        case CCPdfDocument::PageNavigationError::PAGE_UNDERFLOW:
            indicator.new_page = invokee_document->total_pages() - 1;
            indicator.req_follow_indicator = true;
        break;
        case CCPdfDocument::PageNavigationError::PAGE_UNEXSITS:
            /*
             *  then we need to handle the errors, user must
             *  make a mistake to operate an invalid document handle
            */
            QMessageBox::critical(invoker,
                                  "Error Occurs!",
                                  "You haven't select a pdf document, select one yeah!");
            indicator.req_follow_indicator = false;
        break;
    }
    /* return backs the indicator, thus the process handling ends */
    return indicator;
}


CCPdfNavigationPolicy::CCPdfNavigationPolicy() {
    /* promise a def behaviour */
    page_navigate_functor = def_indicate;
}
