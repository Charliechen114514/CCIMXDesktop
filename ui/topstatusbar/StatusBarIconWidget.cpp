#include "StatusBarIconWidget.h"

StatusBarIconWidget::StatusBarIconWidget(QString selfLabeledName, QWidget* parent)
    : QWidget { parent }
    , self_labeled_name(selfLabeledName) {
}

void StatusBarIconWidget::adjustSelfHeight(int height) {
    setFixedHeight(height);
}

QString StatusBarIconWidget::labeledName() const{ return self_labeled_name; }

bool StatusBarIconWidget::processIconsEvent(IconEvent* icons) {
    if (icons->target != this) {
        return false; ///< don't matching these
    }
    /*
     * Empty's, which means default we ignores the sessions
     */
    return iconEvents(icons); ///< means the object ignores the sessions
}

bool StatusBarIconWidget::iconEvents(IconEvent *icons) { return false; }

IconEvent::IconEvent(StatusBarIconWidget *target, QObject *parent)
    : QObject(parent)
    , target(target) { }
