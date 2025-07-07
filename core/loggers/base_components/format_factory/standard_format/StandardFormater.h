#ifndef STANDARDFORMATER_H
#define STANDARDFORMATER_H

#include "../FormativeFactory.h"

/**
 * @class StandardFormater
 * @brief A concrete implementation of FormativeFactory for standard log formatting.
 *
 * This class provides configurable formatting options for log messages,
 * including timestamp, file, line, and function information display.
 */
class StandardFormater : public FormativeFactory {
public:
    StandardFormater() = default;

    /**
     * @struct LogFormatOptions
     * @brief Configuration options for log message formatting
     */
    struct LogFormatOptions {
        bool showTimestamp = true; /**< Enable/disable timestamp display */
        bool showFile = false; /**< Enable/disable source file display */
        bool showLine = false; /**< Enable/disable line number display */
        bool showFunction = false; /**< Enable/disable function name display */
    };

    /**
     * @brief Formats a log message according to configured options
     * @param type The log message type (debug, warning, etc.)
     * @param context The log message context (file, line, function)
     * @param msg The actual log message
     * @return Formatted log message as QString
     */
    QString formativeFactory(
        QtMsgType type,
        const QMessageLogContext& context,
        const QString& msg) override;

    /**
     * @brief Enable/disable timestamp display
     * @param enable True to show timestamps, false to hide
     */
    void setShowTimestamp(bool enable);

    /**
     * @brief Enable/disable source file display
     * @param enable True to show file names, false to hide
     */
    void setShowFile(bool enable);

    /**
     * @brief Enable/disable line number display
     * @param enable True to show line numbers, false to hide
     */
    void setShowLine(bool enable);

    /**
     * @brief Enable/disable function name display
     * @param enable True to show function names, false to hide
     */
    void setShowFunction(bool enable);

    /**
     * @brief Set all formatting options at once
     * @param options The complete set of formatting options
     */
    void setOptions(const LogFormatOptions& options);

    /**
     * @brief Get current formatting options
     * @return Current formatting options
     */
    LogFormatOptions options() const;

private:
    /**
     * @brief Convert QtMsgType to human-readable string
     * @param type The message type to convert
     * @return String representation of the message type
     */
    QString from_type(QtMsgType type);

    LogFormatOptions options_; /**< Current formatting options */
};

#endif // STANDARDFORMATER_H
