#ifndef UIPAGENAVIGATIONPOLICY_H
#define UIPAGENAVIGATIONPOLICY_H
#include <QString>

namespace UiPageNavigationPolicy {
/**
 * @brief label_disp_indicator
 * This function is used to display the current page and total pages.
 * @param cur current page
 * @param tol total pages
 * @return QString representation of the current and total pages
 */
QString label_disp_indicator(int cur, int tol);
};

#endif // UIPAGENAVIGATIONPOLICY_H
