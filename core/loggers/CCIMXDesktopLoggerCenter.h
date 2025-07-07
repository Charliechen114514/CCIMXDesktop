#ifndef CCIMXDESKTOPLOGGERCENTER_H
#define CCIMXDESKTOPLOGGERCENTER_H

#include "library/simple_gerseter/simple_getseter.hpp"
#include <QDebug>

class QMutex;
class DesktopLoggerBackends;

/**
 * @class CCIMXDesktopLoggerCenter
 * @brief Central logging management system for CCIMXDesktop
 *
 * This class provides a centralized logging system that manages multiple logging backends,
 * handles message broadcasting, and maintains logging sessions.
 */
class CCIMXDesktopLoggerCenter {
public:
    /**
     * @brief Destructor
     */
    ~CCIMXDesktopLoggerCenter();

    /**
     * @brief Gets the global singleton instance
     * @return Reference to the global logger center instance
     */
    static CCIMXDesktopLoggerCenter& global_instance();

    __PROPERTY_GETSET(bool, broadcast_to_old); ///< @property Property for broadcast_to_old setting

    /**
     * @brief Registers a new logging backend
     * @param backend Pointer to the backend to register
     */
    void registerBackend(DesktopLoggerBackends* backend);

    /**
     * @brief Gets a snapshot of all registered backends
     * @return Vector of shared pointers to all backends
     */
    std::vector<std::shared_ptr<DesktopLoggerBackends>> backend_shots() const;

    /**
     * @brief Removes a logging backend
     * @param backend Pointer to the backend to remove
     * @return true if removal was successful, false otherwise
     */
    bool removeBackend(DesktopLoggerBackends* backend);

    /**
     * @brief Makes only the specified backend available for logging
     * @param backend Pointer to the backend to make exclusively available
     */
    void availableTargetBackendOnly(DesktopLoggerBackends* backend);

    /**
     * @brief Makes all backends available for logging
     */
    void availableBackends();

    /**
     * @brief Disables logging for specific backend
     * @param backend Pointer to the backend to disable
     */
    void disableTargetBackends(DesktopLoggerBackends* backend);

    /**
     * @brief Silences all logging backends
     */
    void silentBackends();

private:
    /**
     * @brief Private constructor for singleton pattern
     */
    CCIMXDesktopLoggerCenter();

    Q_DISABLE_COPY_MOVE(CCIMXDesktopLoggerCenter); ///< Disable copy and move operations

    bool broadcast_to_old { false }; ///< When true, broadcasts messages to the previous handler
    QtMessageHandler old_handler { nullptr }; ///< Stores the previous Qt message handler

    /**
     * @brief Global message handler for Qt logging system
     * @param type The type of message (debug, warning, etc.)
     * @param ctx The message context (file, line, function)
     * @param msg The message content
     */
    static void globalMessageHandler(QtMsgType type, const QMessageLogContext& ctx, const QString& msg);

    std::shared_ptr<QMutex> mutex; ///< Mutex for thread-safe operations
    std::vector<std::shared_ptr<DesktopLoggerBackends>> backends; ///< Collection of logging backends
};

#endif // CCIMXDESKTOPLOGGERCENTER_H
