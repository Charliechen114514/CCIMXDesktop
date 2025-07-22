/**
 * @file FileMonitor.h
 * @brief Defines the FileMonitor class, a utility for monitoring changes in a file directory.
 */

#ifndef FILEMONITOR_H
#define FILEMONITOR_H

#include <QObject> // Base class for FileMonitor, enabling signals/slots
#include <QSet> // For storing sets of file paths for comparison
#include <memory> // Required for std::shared_ptr

// Forward declarations to avoid heavy includes
class QMutex;
class QTimer; // Required for the timer_scan member

/**
 * @class FileMonitor
 * @brief Monitors a specified directory for file additions or deletions at regular intervals.
 *
 * The FileMonitor class provides a mechanism to observe a given directory and
 * detect changes within it, specifically the creation of new files or the deletion
 * of existing ones. It operates by periodically scanning the directory and comparing
 * its current state with a previously recorded state. Signals are emitted upon
 * detecting changes, or when its monitoring parameters (path, interval, state) change.
 * Thread-safe access to internal state is ensured using a QMutex.
 */
class FileMonitor : public QObject {
    Q_OBJECT

    /**
     * @brief The default monitoring scan interval in milliseconds.
     * This constant defines how often the directory will be scanned for changes.
     */
    static constexpr const int MONIT_INTV = 2000; // 2000 milliseconds = 2 seconds

public:
    /**
     * @brief Constructs a FileMonitor object.
     * @param path The initial directory path to monitor.
     * @param parent A pointer to the parent QObject, allowing for proper object hierarchy and memory management. Defaults to nullptr.
     */
    explicit FileMonitor(const QString& path, QObject* parent = nullptr);

    /**
     * @brief Sets the directory path to be monitored.
     * 	 * If the new path is different from the current one, the monitor's state
     * is reset, and a `monitoringChanged` signal is emitted.
     * @param newPath The new directory path to monitor.
     */
    void setMonitorDirent(const QString& newPath);

    /**
     * @brief Returns the current directory path being monitored.
     * @return A QString containing the path of the monitored directory.
     */
    QString monitorDirent() const;

    /**
     * @brief Sets the interval (in milliseconds) at which the directory will be scanned.
     * 	 * If the new interval is different, the timer is updated, and a `monitoringIntervalChanged`
     * signal is emitted.
     * @param interval The new scan interval in milliseconds.
     */
    void setMonitorScanInterval(const int interval);

    /**
     * @brief Returns the current monitoring scan interval.
     * @return The scan interval in milliseconds.
     */
    int monitorScanInterval() const;

    /**
     * @brief Sets the monitoring state (active or inactive).
     * 	 * When set to true, the monitor starts scanning. When set to false, it stops.
     * A `monitoringStateChanged` signal is emitted upon state change.
     * @param st True to start monitoring, false to stop.
     */
    void setMonitoringState(bool st);

    /**
     * @brief Returns the current monitoring state.
     * @return True if monitoring is active, false otherwise.
     */
    bool monitoringState() const;

signals:
    /**
     * @brief Signal emitted when new files are detected in the monitored directory.
     * @param files A QStringList containing the absolute paths of the newly detected files.
     */
    void newFiles(const QStringList& files);

    /**
     * @brief Signal emitted when files are detected as deleted from the monitored directory.
     * @param files A QStringList containing the absolute paths of the deleted files.
     */
    void deletedFiles(const QStringList& files);

    /**
     * @brief Signal emitted when the monitored directory path changes.
     * @param path The new path being monitored.
     */
    void monitoringChanged(const QString& path);

    /**
     * @brief Signal emitted when the monitoring scan interval changes.
     * @param new_interval The new scan interval in milliseconds.
     */
    void monitoringIntervalChanged(const int new_interval);

    /**
     * @brief Signal emitted when the monitoring state (active/inactive) changes.
     * @param new_state The new monitoring state (true for active, false for inactive).
     */
    void monitoringStateChanged(const bool new_state);

private slots:
    /**
     * @brief Processes the file comparison session.
     * 	 * This slot is connected to the internal timer. It performs a scan of the
     * monitored directory, compares it with the previous state, and emits
     * `newFiles` or `deletedFiles` signals as appropriate.
     */
    void processCompareSession();

private:
    QString monitoring_folder; ///< The directory path currently being monitored.
    QTimer* timer_scan; ///< QTimer to trigger periodic directory scans.
    QSet<QString> scanFiles() const; ///< Helper function to scan the directory and return a set of current file paths.
    QSet<QString> prevFiles; ///< Stores the set of file paths from the previous scan for comparison.
    std::shared_ptr<QMutex> mutex; ///< A shared pointer to a QMutex for protecting concurrent access to internal data.
};

#endif // FILEMONITOR_H
