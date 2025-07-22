/**
 * @file ToastProxy.h
 * @brief Defines the ToastProxy class, an intermediary for processing and forwarding toast notifications.
 */

#ifndef TOASTPROXY_H
#define TOASTPROXY_H

#include "core/server/toast_file_gen_and_receiver/ToastMetaProtocol.h" // Includes the data structure for toast messages
#include <QObject> // Base class for ToastProxy, enabling signals/slots

// Forward declaration to avoid circular dependencies and improve compilation time
class DesktopToast;

/**
 * @class ToastProxy
 * @brief Acts as an intermediary to process and forward toast notifications to the display mechanism.
 *
 * The ToastProxy receives `ToastMetaProtocol` objects, which encapsulate toast notification data.
 * Its primary role is to take this data and pass it to a `DesktopToast` instance, which is
 * responsible for rendering and displaying the actual toast notification on the user's desktop.
 * This separation allows for decoupling the toast data generation/reception from its display logic.
 */
class ToastProxy : public QObject {
    Q_OBJECT

public:
    /**
     * @brief Deleted default constructor.
     * 	 * This ensures that `ToastProxy` objects can only be constructed with a `DesktopToast`
     * and a parent `QObject`, reinforcing its role as an intermediary.
     */
    ToastProxy() = delete;

    /**
     * @brief Constructs a ToastProxy instance.
     * @param toast A pointer to the `DesktopToast` object that will display the toast notifications.
     * The proxy does not take ownership of this object.
     * @param parent A pointer to the parent `QObject` for this proxy, allowing for proper
     * object hierarchy and memory management.
     */
    explicit ToastProxy(DesktopToast* toast, QObject* parent);

public slots:
    /**
     * @brief Processes an incoming `ToastMetaProtocol`.
     * 	 * This slot is designed to receive `ToastMetaProtocol` objects. Upon reception,
     * it will extract the necessary information and typically forward it to the
     * associated `DesktopToast` instance for display.
     * @param protocolMeta A constant reference to the `ToastMetaProtocol` containing the toast data.
     */
    void process_toastMeta(const ToastMetaProtocol& protocolMeta);

private:
    /**
     * @brief A pointer to the `DesktopToast` object responsible for displaying toast notifications.
     * 	 * This is the ultimate destination for the `ToastMetaProtocol` data, where the actual
     * visual notification will be rendered.
     */
    DesktopToast* toast;
};

#endif // TOASTPROXY_H
