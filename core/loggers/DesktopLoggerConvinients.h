#ifndef DESKTOPLOGGERCONVINIENTS_H
#define DESKTOPLOGGERCONVINIENTS_H
class QString;

/**
 * @namespace Logger
 * @brief Provides thread-safe logging utilities for different severity levels
 *
 * This namespace contains convenience functions for logging messages
 * at standard severity levels. All functions are thread-safe and
 * use the application's centralized logging infrastructure.
 */
namespace Logger {

/**
 * @brief Log a debug message
 * @param info The debug message to log
 * @note These messages are typically only visible in debug builds
 */
void postDebug(const QString& info);

/**
 * @brief Log an informational message
 * @param info The informational message to log
 * @note These messages indicate normal application operation
 */
void postInfo(const QString& info);

/**
 * @brief Log a warning message
 * @param info The warning message to log
 * @note These messages indicate potential issues that aren't critical
 */
void postWarning(const QString& info);

/**
 * @brief Log an error message
 * @param info The error message to log
 * @note These messages indicate serious problems that affect functionality
 */
void postError(const QString& info);

/**
 * @brief Log a fatal error message
 * @param info The fatal error message to log
 * @note These messages indicate critical failures that may terminate the application
 */
void postFatal(const QString& info);

} // namespace Logger

#endif // DESKTOPLOGGERCONVINIENTS_H
