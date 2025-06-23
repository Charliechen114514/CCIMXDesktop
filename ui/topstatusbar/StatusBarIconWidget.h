#ifndef STATUSBARICONWIDGET_H
#define STATUSBARICONWIDGET_H

/**
 * @file statusbariconwidget.h
 * @brief Declares the StatusBarIconWidget and related classes for the top status bar.
 */

#include <QWidget>

class StatusBarIconWidget;

/**
 * @class IconEvent
 * @brief Represents a custom event targeting a specific StatusBarIconWidget.
 *
 * IconEvent is used to deliver status or behavior change notifications to
 * instances of StatusBarIconWidget.
 */
struct IconEvent : public QObject {
    /**
     * @brief Constructs an IconEvent.
     * @param target Pointer to the target widget this event is intended for.
     * @param parent Optional QObject parent.
     */
    explicit IconEvent(StatusBarIconWidget* target, QObject* parent);

    /**
     * @brief Destroys the IconEvent.
     */
    virtual ~IconEvent() = default;
    ;

    /**
     * @brief Pointer to the target StatusBarIconWidget.
     */
    const StatusBarIconWidget* target;
};

/**
 * @class StatusBarIconWidget
 * @brief Abstract base widget class representing an icon in the status bar.
 *
 * Each StatusBarIconWidget instance has a labeled name and optionally responds
 * to IconEvent instances. Subclass this for specific icons like network, battery, etc.
 */
class StatusBarIconWidget : public QWidget {
    Q_OBJECT

public:
    /**
     * @brief Constructs a StatusBarIconWidget.
     * @param labeled_name The identifier label for this icon.
     * @param parent Optional parent QWidget.
     */
    explicit StatusBarIconWidget(QString labeled_name, QWidget* parent = nullptr);

    /**
     * @brief Destroys the StatusBarIconWidget.
     */
    virtual ~StatusBarIconWidget() = default;

    /**
     * @brief Adjusts the widget's height to a fixed value.
     * @param height Height in pixels.
     */
    virtual void adjustSelfHeight(int height);

    /**
     * @brief Returns the labeled name of this icon.
     * @return The label as a QString.
     */
    QString labeledName() const;

    /**
     * @brief Handles an IconEvent.
     * @param icons The IconEvent to process.
     * @return True if the event was processed, false otherwise.
     */
    bool processIconsEvent(IconEvent* icons);

    /**
     * @brief Virtual handler for icon events. Override in subclasses.
     * @param icons The IconEvent to process.
     * @return True if handled; false to ignore.
     */
    virtual bool iconEvents(IconEvent* icons);
    ;

private:
    /**
     * @brief The labeled name used to identify this icon.
     */
    const QString self_labeled_name;
};

#endif // STATUSBARICONWIDGET_H
