/**
 * @file ToastReceiver.h
 * @brief Defines the ToastReceiver class, responsible for receiving and parsing toast notification data.
 */

#ifndef TOASTRECEIVER_H
#define TOASTRECEIVER_H

#include "ToastMetaProtocol.h" // Includes the data structure for toast messages
#include <QObject> // Base class for ToastReceiver, enabling signals/slots
#include <optional> // For std::optional in fromExternalJsonString

// Forward declaration to avoid heavy includes
class FileMonitor;

/**
 * @class ToastReceiver
 * @brief Receives toast notification data, often from external sources, and emits it for processing.
 *
 * This class acts as a listener for toast notification data. It is typically
 * connected to a `FileMonitor` to detect new toast-related files (e.g., JSON files)
 * and then parses these files into `ToastMetaProtocol` objects. Once successfully
 * parsed, it emits a signal to notify other components (like a `ToastProxy` or `ToastPostServer`)
 * that a new toast is ready to be displayed.
 */
class ToastReceiver : public QObject {
    Q_OBJECT

public:
    /**
     * @brief Constructs a ToastReceiver instance.
     * @param parent A pointer to the parent `QObject`, often a `FileMonitor` that this receiver
     * will be associated with for detecting incoming toast data. Defaults to `nullptr`.
     */
    explicit ToastReceiver(FileMonitor* parent = nullptr);

    /**
     * @brief Parses a JSON string from an external source into a `ToastMetaProtocol` object.
     * 	 * This method attempts to read and parse the content of a JSON file (specified by `json_file`)
     * into a `ToastMetaProtocol` struct. It returns `std::nullopt` if the file cannot be read,
     * is not valid JSON, or does not contain the expected toast metadata.
     * @param json_file The path to the JSON file containing the toast metadata.
     * @return An `std::optional<ToastMetaProtocol>` containing the parsed toast data if successful,
     * otherwise `std::nullopt`.
     */
    std::optional<ToastMetaProtocol> fromExternalJsonString(const QString& json_file) const;

signals:
    /**
     * @brief Signal emitted when a new toast notification is ready to be posted.
     * 	 * This signal carries the parsed `ToastMetaProtocol` data and should be connected
     * to a slot responsible for displaying the toast.
     * @param protocolMeta A constant reference to the `ToastMetaProtocol` object containing the toast data.
     */
    void postToast(const ToastMetaProtocol& protocolMeta);

private slots:
    /**
     * @brief Processes a list of new toast metadata strings.
     * 	 * This slot is typically connected to a signal from a `FileMonitor` that
     * provides a list of paths to new or updated toast metadata files (e.g., JSON files).
     * It iterates through the list, parses each file using `fromExternalJsonString`,
     * and emits `postToast` for each successfully parsed toast.
     * @param toasts_metas A `QStringList` containing paths to the toast metadata files.
     */
    void process_newToast(const QStringList& toasts_metas);

private:
    /**
     * @brief A pointer to the `FileMonitor` instance.
     * 	 * This monitor is responsible for watching a specific directory for new
     * or changed files that represent toast notifications.
     */
    FileMonitor* monitor;
};

#endif // TOASTRECEIVER_H
