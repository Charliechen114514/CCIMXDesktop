#ifndef STATUSBARICONWIDGET_H
#define STATUSBARICONWIDGET_H

#include <QWidget>
class StatusBarIconWidget;
/**
 * @brief The IconEvent class
 */
struct IconEvent : public QObject {
    explicit IconEvent(StatusBarIconWidget* target, QObject* parent)
        : QObject(parent)
        , target(target) { }
    virtual ~IconEvent() = default;
    const StatusBarIconWidget* target;
};

/**
 * @brief The StatusBarIconWidget class
 * is the Icon Interfaces like widget for
 * the icon statusbar
 */
class StatusBarIconWidget : public QWidget {
	Q_OBJECT
public:
    /**
     * @brief StatusBarIconWidget creator
     * @param parent
     */
    explicit StatusBarIconWidget(QString labeled_name, QWidget* parent = nullptr);
    /* set to the fixed size */
    virtual ~StatusBarIconWidget() = default;
    virtual void adjustSelfHeight(int height) {
        setFixedHeight(height);
    }
    QString labeledName() const { return self_labeled_name; }

    bool processIconsEvent(IconEvent* icons);
    virtual bool iconEvents(IconEvent* icons) { return false; }

private:
    const QString self_labeled_name;
};

#endif // STATUSBARICONWIDGET_H
