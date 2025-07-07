#ifndef CONSOLELOGGER_H
#define CONSOLELOGGER_H

#include "DesktopLoggerBackends.h"

/**
 * @class ConsoleLogger
 * @brief A logger backend that outputs messages to the console
 *
 * This class implements a console-based logger that can format messages
 * in different styles for console output.
 */
class ConsoleLogger : public DesktopLoggerBackends {
public:
    /**
     * @enum ConsoleFormatStyle
     * @brief Defines the available formatting styles for console output
     */
    enum class ConsoleFormatStyle {
        Plain, /**< Simple plain text format */
        LoguruLike /**< Format similar to Loguru logger (with colors and metadata) */
    };

    /**
     * @brief Constructs a ConsoleLogger with specified format style
     * @param type The formatting style to use (defaults to Plain)
     */
    explicit ConsoleLogger(ConsoleFormatStyle type = ConsoleFormatStyle::Plain);

    /**
     * @brief Destructor (default implementation)
     */
    ~ConsoleLogger() override = default;

    /**
     * @brief Posts the current status of the logger to the console
     * @return true if the status was successfully posted, false otherwise
     */
    bool postSelfStatus() override;
};

#endif // CONSOLELOGGER_H
