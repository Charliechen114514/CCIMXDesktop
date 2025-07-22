/**
 * @file HomeCardManager.h
 * @brief Defines the HomeCardManager class, responsible for managing widgets within a QStackedWidget.
 */

#ifndef HOMECARDMANAGER_H
#define HOMECARDMANAGER_H

#include <QtClassHelperMacros> // Assuming this provides Q_DISABLE_COPY_MOVE
#include <memory> // Required for std::shared_ptr

// Forward declarations to reduce compilation dependencies
class QStackedWidget;
class QWidget;
class QMutex;

/**
 * @class HomeCardManager
 * @brief Manages a collection of QWidget instances displayed within a QStackedWidget.
 *
 * This class provides an interface for adding, removing, and querying the number of
 * "cards" (widgets) managed by a QStackedWidget. It ensures thread-safe operations
 * on the managed widgets through the use of a QMutex.
 *
 * @note This class is non-copyable and non-movable to ensure a single, controlled
 * instance managing the QStackedWidget.
 */
class HomeCardManager {
public:
    /**
     * @brief Constructs a HomeCardManager instance.
     * @param widget A pointer to the QStackedWidget that this manager will control.
     * The manager does not take ownership of the QStackedWidget.
     */
    explicit HomeCardManager(QStackedWidget* widget);

    /**
     * @brief Disables copy construction and copy assignment for HomeCardManager.
     * 	 * This macro ensures that instances of HomeCardManager cannot be copied,
     * enforcing a single point of control over the managed QStackedWidget.
     */
    Q_DISABLE_COPY_MOVE(HomeCardManager);

    /**
     * @brief Installs a new widget into the managed QStackedWidget.
     * 	 * This method adds the provided widget to the QStackedWidget, making it
     * available for display. It handles thread-safe access to the stacked widget.
     * @param widget A pointer to the QWidget to be installed. The manager takes ownership
     * of the widget if the QStackedWidget takes ownership.
     */
    virtual void installWidget(QWidget* widget);

    /**
     * @brief Removes a widget from the managed QStackedWidget.
     * 	 * This method removes the specified widget from the QStackedWidget.
     * It handles thread-safe access. The caller is responsible for deleting the widget
     * if the QStackedWidget does not manage its lifetime.
     * @param widget A pointer to the QWidget to be removed.
     */
    virtual void removeWidget(QWidget* widget);

    /**
     * @brief Returns the number of accessible cards (widgets) currently managed.
     * 	 * This method provides a count of the widgets that are currently part of the
     * QStackedWidget managed by this class. It ensures thread-safe access to this count.
     * @return The integer count of accessible widgets.
     */
    virtual int accessible_card_cnt() const;

protected:
    /**
     * @brief A pointer to the QStackedWidget managed by this class.
     * 	 * This member holds the reference to the QStackedWidget where the "cards"
     * (individual widgets) are displayed.
     */
    QStackedWidget* stacked_widget;

    /**
     * @brief A shared pointer to a QMutex for thread-safe access.
     * 	 * This mutex is used to protect concurrent access to the `stacked_widget`
     * and its operations, ensuring data integrity in multithreaded environments.
     */
    std::shared_ptr<QMutex> mutex;
};

#endif // HOMECARDMANAGER_H
