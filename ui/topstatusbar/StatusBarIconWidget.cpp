#include "StatusBarIconWidget.h"

StatusBarIconWidget::StatusBarIconWidget(QString selfLabeledName, QWidget* parent)
    : QWidget { parent }
    , self_labeled_name(selfLabeledName) {
}

bool StatusBarIconWidget::processIconsEvent(IconEvent* icons) {
    if (icons->target != this) {
        return false; ///< don't matching these
    }
    /*
     * Empty's, which means default we ignores the sessions
     */
    return iconEvents(icons); ///< means the object ignores the sessions
}
