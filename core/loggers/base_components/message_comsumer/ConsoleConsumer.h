#ifndef CONSOLECONSUMER_H
#define CONSOLECONSUMER_H

#include "LoggerBaseConsumer.h"

/**
 * @class ConsoleConsumer
 * @brief A consumer that outputs log messages to the console
 *
 * This class implements the LoggerBaseConsumer interface to provide
 * console output functionality for log messages.
 */
class ConsoleConsumer : public LoggerBaseConsumer {
public:
    ConsoleConsumer() = default;

    /**
     * @brief Outputs a log message to the console
     * @param message The log message to be consumed (rvalue reference)
     * @return true if the message was successfully consumed, false otherwise
     */
    bool consume_message(const QString&& message) override;

    /**
     * @brief Gets the last error message
     * @return The last error message as QString
     */
    inline QString errorString() const override { return errorStr; }

private:
    QString errorStr; /**< Stores the last error message */
};

#endif // CONSOLECONSUMER_H
