#include "uipagenavigationpolicy.h"

namespace UiPageNavigationPolicy
{


QString label_disp_indicator(int cur, int tol)
{
    return QString("Cur: %1 Tol: %2").arg(cur).arg(tol);
}

} // UiPageNavigationPolicy Ends


