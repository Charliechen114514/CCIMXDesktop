#ifndef PROCESSBROSWER_H
#define PROCESSBROSWER_H

#include <QObject>
#include <QTimer>

/* Forward declaration of platform-specific driver */
class CCIMX_AbstractProcessBroswerDriver;

/**
 * @brief The ProcessBroswer class
 * Provides an interface to retrieve and monitor system processes information.
 * Acts as a process browser that periodically fetches process data.
 */
class ProcessBroswer : public QObject {
    Q_OBJECT
public:
    /**
     * @brief Constructor with optional parent.
     * @param parent Pointer to the QObject parent, default nullptr.
     */
    explicit ProcessBroswer(QObject* parent = nullptr);

    /**
     * @brief Destructor cleans up resources.
     */
    ~ProcessBroswer();

    /**
     * @brief The ProcessInfo struct
     * Holds detailed information about a system process.
     */
    struct ProcessInfo {
        int pid; ///< Process ID.
        int ppid; ///< Parent Process ID.
        QString name; ///< Process name.
        QString fullPath; ///< Full executable path of the process.
        int threadCount; ///< Number of threads in the process.
        qint64 memoryUsageKB; ///< Memory usage in kilobytes.
        double cpuPercent; ///< CPU usage percentage.
        QString userName; ///< User who owns the process.
    };

    /**
     * @brief set_flush_freq
     * Sets the frequency (in milliseconds) at which process data is refreshed.
     * @param msecs Refresh interval in milliseconds.
     */
    void set_flush_freq(const int msecs) { flush_msecs = msecs; }

    /**
     * @brief set_capture_state
     * Enables or disables process data capturing.
     * @param st True to start capturing, false to stop.
     */
    void set_capture_state(bool st);

signals:
    /**
     * @brief fetch_finish
     * Signal emitted when process data is fetched and ready.
     * @param infos List of ProcessInfo structures with current process data.
     */
    void fetch_finish(const QList<ProcessBroswer::ProcessInfo>& infos);

private:
    CCIMX_AbstractProcessBroswerDriver* platform_driver_base { nullptr }; ///< Platform-specific driver instance.

    /**
     * @brief setup_platform_relative
     * Setup the platform-specific process browser driver.
     */
    void setup_platform_relative();

    /**
     * @brief flush_once
     * Called periodically to refresh process data from the driver.
     */
    void flush_once();

    int flush_msecs { 1500 }; ///< Refresh interval in milliseconds.
    QList<ProcessInfo> process_list; ///< Cached list of processes.
    QTimer flush_timer; ///< Timer to schedule periodic updates.
};

/**
 * @brief The CCIMX_AbstractProcessBroswerDriver class
 * Abstract base class for platform-specific process browser drivers.
 * Implementations should populate the process list data.
 */
class CCIMX_AbstractProcessBroswerDriver {
public:
    CCIMX_AbstractProcessBroswerDriver() = default;
    virtual ~CCIMX_AbstractProcessBroswerDriver() = default;

    /**
     * @brief factory
     * Populate the list with current system processes information.
     * @param lists Reference to a list to be filled with ProcessInfo data.
     */
    virtual void factory(QList<ProcessBroswer::ProcessInfo>& lists) = 0;
};

#endif // PROCESSBROSWER_H
