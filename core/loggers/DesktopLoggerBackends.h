#ifndef DESKTOPLOGGERBACKENDS_H
#define DESKTOPLOGGERBACKENDS_H

#include "library/simple_gerseter/simple_getseter.hpp"
#include <QMutex>
#include <QString>
#include <QtLogging>

class QMessageLogContext;
class QString;
class FormativeFactory;
class LoggerBaseConsumer;

/**
 * @class DesktopLoggerBackends
 * @brief Base class for all desktop logger backend implementations
 *
 * Provides core functionality for message processing and routing between
 * formatters and consumers, with thread-safe operations.
 */
struct DesktopLoggerBackends {
public:
    DesktopLoggerBackends() = delete;

    /**
     * @brief Constructs a logger backend with formatter and consumer
     * @param factory The message formatter factory
     * @param consumer The message consumer backend
     */
    DesktopLoggerBackends(std::shared_ptr<FormativeFactory> factory,
                          std::shared_ptr<LoggerBaseConsumer> consumer);

    /**
     * @brief Virtual destructor
     */
    virtual ~DesktopLoggerBackends() = default;

    /**
     * @enum LogStatus
     * @brief Status codes for log processing operations
     */
    enum LogStatus {
        LogSuccess = 0, /**< Message was processed successfully */
        LogDisabled = 1, /**< Logger is currently disabled */
        LogFailed = 2 /**< Message processing failed */
    };

    /**
     * @brief Processes a log message through formatter and consumer
     * @param type The message severity type
     * @param context The logging context information
     * @param msg The message content
     * @return Status of the processing operation
     */
    virtual LogStatus processMessage(QtMsgType type,
                                     const QMessageLogContext& context,
                                     const QString& msg);

    /**
     * @brief Posts the current status of the logger
     * @return true if status was posted successfully
     * @note Pure virtual function must be implemented by derived classes
     */
    virtual bool postSelfStatus() = 0;

    __PROPERTY_GETSET(bool, enabled); ///< @property Property for enabled state management

    /**
     * @brief Replaces the formatter factory at runtime
     * @param factory The new formatter factory to install
     */
    void hot_install_factory(std::shared_ptr<FormativeFactory> factory);

    /**
     * @brief Replaces the message consumer at runtime
     * @param consumer The new consumer backend to install
     */
    void hot_install_consumer(std::shared_ptr<LoggerBaseConsumer> consumer);

protected:
    bool enabled { true }; /**< Current enabled state of the logger */
    QMutex lock; /**< Mutex for thread-safe operations */
    std::shared_ptr<FormativeFactory> format_factory; /**< Message formatter */
    std::shared_ptr<LoggerBaseConsumer> message_consume_backend; /**< Message consumer */
};

#endif // DESKTOPLOGGERBACKENDS_H
