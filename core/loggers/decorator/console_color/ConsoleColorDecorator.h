#ifndef CONSOLECOLORDECORATOR_H
#define CONSOLECOLORDECORATOR_H

#include "core/loggers/base_components/format_factory/FormativeFactory.h"

/**
 * @class ConsoleColorDecorator
 * @brief Decorator pattern implementation for adding ANSI color codes to log messages
 *
 * This class extends FormativeFactory to add color formatting to log messages
 * based on their message type (error, warning, info, etc.).
 */
class ConsoleColorDecorator : public FormativeFactory {
    static constexpr const char* RESET = "\033[0m"; /**< ANSI reset color code */
    static constexpr const char* RED = "\033[31m"; /**< ANSI red color code */
    static constexpr const char* GREEN = "\033[32m"; /**< ANSI green color code */
    static constexpr const char* YELLOW = "\033[33m"; /**< ANSI yellow color code */
    static constexpr const char* BLUE = "\033[34m"; /**< ANSI blue color code */
    static constexpr const char* CYAN = "\033[36m"; /**< ANSI cyan color code */

public:
    /**
     * @brief Constructs a ConsoleColorDecorator wrapping another FormativeFactory
     * @param other_factory Pointer to the FormativeFactory to be decorated
     */
    ConsoleColorDecorator(FormativeFactory* other_factory);

    /**
     * @brief Default destructor
     */
    ~ConsoleColorDecorator() override = default;

    /**
     * @brief Formats and colors a log message based on its type
     * @param type The severity/type of the message
     * @param context The logging context (file, line, function)
     * @param msg The actual log message
     * @return Formatted and colored message string
     */
    QString formativeFactory(QtMsgType type, const QMessageLogContext& context, const QString& msg) override;

private:
    std::shared_ptr<FormativeFactory> decorated_factory; /**< The decorated formatter instance */

    /**
     * @brief Gets the ANSI color code for a given message type
     * @param type The message type to get color for
     * @return Corresponding ANSI color code string
     */
    QString from_msgType(QtMsgType type) const;

    /**
     * @brief Gets the default uncolored message
     * @param type The message type
     * @param context The logging context
     * @param msg The original message
     * @return Unmodified message string
     */
    inline const QString get_default_type(QtMsgType type, const QMessageLogContext& context, const QString& msg) const {
        return msg;
    }
};

#endif // CONSOLECOLORDECORATOR_H
