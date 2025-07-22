/**
 * @file ToastPostServer.h
 * @brief Defines the ToastPostServer class, a server for managing and posting toast notifications.
 */

#ifndef TOASTPOSTSERVER_H
#define TOASTPOSTSERVER_H

#include "core/server/DesktopServerBase.h" // Base class for server functionalities
#include <memory> // Required for std::shared_ptr

// Forward declarations to avoid heavy includes and circular dependencies
class ToastReceiver;
class DesktopToast;
class ToastProxy;

/**
 * @brief The ToastPostServer class
 * @brief Manages the reception and display of toast notifications.
 *
 * This server is responsible for handling incoming toast information. It likely
 * receives toast messages (possibly via a `ToastReceiver` or `ToastProxy`),
 * processes them, and then instructs a `DesktopToast` component to display
 * the actual notification to the user.
 *
 * It inherits from `DesktopServerBase`, suggesting it operates as a background
 * service or manager within a desktop application context.
 */
class ToastPostServer : public DesktopServerBase {
    Q_OBJECT

public:
    /**
     * @brief Constructs a ToastPostServer instance.
     * @param toast A pointer to the DesktopToast object responsible for displaying the actual toast UI.
     * The server does not take ownership of this object.
     * @param monitoring_path A QString representing a path that the server might monitor for toast-related data or events.
     * This could be a directory for toast files, a named pipe, or similar.
     * @param parent A pointer to the parent QObject, allowing for proper object hierarchy and memory management.
     */
    ToastPostServer(DesktopToast* toast, const QString& monitoring_path, QObject* parent);

private:
    /**
     * @brief A shared pointer to a ToastProxy object.
     * 	 * This proxy likely acts as an intermediary or an interface for clients
     * to send toast notifications to this server, potentially abstracting
     * the underlying communication mechanism.
     */
    std::shared_ptr<ToastProxy> toastProxy;

    /**
     * @brief A pointer to a ToastReceiver object.
     * 	 * This receiver component is likely responsible for listening for and
     * receiving toast messages from various sources, feeding them into the server.
     */
    ToastReceiver* receiver;
};

#endif // TOASTPOSTSERVER_H
