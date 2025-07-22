/**
 * @file ToastMetaProtocol.h
 * @brief Defines the ToastMetaProtocol struct, used for encapsulating data for toast notifications.
 */

#ifndef TOASTMETAPROTOCOL_H
#define TOASTMETAPROTOCOL_H

#include <QDateTime> // For QDateTime to store announcement time
#include <QString> // For QString to hold text data
#include <optional> // For std::optional in from_json_string

/**
 * @struct ToastMetaProtocol
 * @brief Represents the metadata and content for a toast notification.
 *
 * This struct holds information necessary to display a toast notification,
 * including the originating application's name, the message to display,
 * and the time the notification was announced. It provides constructors for
 * easy initialization and methods for serialization to/from JSON strings.
 */
struct ToastMetaProtocol {
    /**
     * @brief The name of the application that generated the toast notification.
     * This can be used to identify the source of the toast.
     */
    QString meta_appName;

    /**
     * @brief The exact date and time when the toast notification was announced.
     * This helps in ordering or time-stamping notifications.
     */
    QDateTime announceTime;

    /**
     * @brief The main message content to be displayed in the toast notification.
     * This is the primary textual information for the user.
     */
    QString meta_displayMessage;

    /**
     * @brief Default constructor for ToastMetaProtocol.
     * Initializes members to their default values (empty strings, null QDateTime).
     */
    ToastMetaProtocol() = default;

    /**
     * @brief Constructs a ToastMetaProtocol with specified application name and message.
     * @param meta_app The name of the application.
     * @param displayMessage The message to be displayed.
     * @param t The announcement time. Defaults to the current system time if not provided.
     */
    ToastMetaProtocol(const QString meta_app, const QString displayMessage, const QDateTime t = QDateTime::currentDateTime());

    /**
     * @brief Constructs a ToastMetaProtocol from a JSON string.
     * 	 * This constructor attempts to parse the provided JSON string and populate
     * the struct members accordingly. It's generally recommended to use
     * `from_json_string` for safer parsing.
     * @param json_string The JSON string representing a ToastMetaProtocol.
     */
    ToastMetaProtocol(const QString& json_string);

    /**
     * @brief Creates an optional ToastMetaProtocol object from a JSON string.
     * 	 * This static method attempts to parse a JSON string and construct a
     * ToastMetaProtocol object. It returns `std::nullopt` if the parsing fails
     * (e.g., invalid JSON format, missing required fields), providing a safe
     * way to deserialize the object.
     * @param json_string The JSON string to parse.
     * @return An `std::optional<ToastMetaProtocol>` containing the parsed object if successful,
     * otherwise `std::nullopt`.
     */
    static std::optional<ToastMetaProtocol> from_json_string(const QString& json_string);

    /**
     * @brief Converts the ToastMetaProtocol object into its JSON string representation.
     * @return A QString containing the JSON representation of the object.
     */
    QString toString() const;
};

#endif // TOASTMETAPROTOCOL_H
