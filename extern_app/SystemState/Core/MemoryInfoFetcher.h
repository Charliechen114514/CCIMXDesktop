#ifndef MEMORYINFOFETCHER_H
#define MEMORYINFOFETCHER_H

#include <QObject>
#include <QTimer>

/* Forward declaration of the driver */
class CCIMX_AbstractMemoryInfoDriver;

/**
 * @brief The MemoryInfoFetcher class
 * Provides memory usage information in a platform-independent manner.
 * Acts as a memory information fetcher interface.
 */
class MemoryInfoFetcher : public QObject {
    Q_OBJECT
public:
    /**
     * @brief format_size
     * Utility function to format byte size into human-readable string.
     * @param size Size in bytes.
     * @return Formatted size string.
     */
    static QString format_size(quint64 size);

    /**
     * @brief Constructor with optional parent.
     * @param parent Pointer to the QObject parent, default is nullptr.
     */
    explicit MemoryInfoFetcher(QObject* parent = nullptr);

    /**
     * @brief Destructor to clean up resources.
     */
    ~MemoryInfoFetcher();
    /**
     * @brief disable copy
     * 
     */
    Q_DISABLE_COPY(MemoryInfoFetcher);

    /**
     * @brief The MemoryStat struct
     * Holds memory statistics at the byte level.
     */
    struct MemoryStat {
        quint64 total_phys_memory; ///< Total physical memory in bytes.
        quint64 avail_phys_memory; ///< Available physical memory in bytes.
        quint64 total_virt_memory; ///< Total virtual memory in bytes.
        quint64 avail_virt_memory; ///< Available virtual memory in bytes.
    } mem_stat; ///< memory stat holder

    /**
     * @brief set_flush_freq
     * Sets the frequency in milliseconds at which memory info is refreshed.
     * @param msecs Flush interval in milliseconds.
     */
    void set_flush_freq(const int msecs) { flush_msecs = msecs; }

    /**
     * @brief set_capture_state
     * Enables or disables memory information capturing.
     * @param st True to start capturing, false to stop.
     */
    void set_capture_state(bool st);

signals:
    /**
     * @brief finish_detect_memory
     * Signal emitted when memory information is updated.
     * @param mem_stat Current memory statistics.
     */
    void finish_detect_memory(const MemoryInfoFetcher::MemoryStat& mem_stat);

private slots:
    /**
     * @brief flush_once
     * Invoked periodically or on demand to update memory statistics by interacting with the driver.
     */
    void flush_once();

private:
    CCIMX_AbstractMemoryInfoDriver* platform_driver_base { nullptr }; ///< Platform-specific driver instance.

    /**
     * @brief setup_platform_relative
     * Sets up the platform-specific memory info driver implementation.
     */
    void setup_platform_relative();

    QTimer flush_timer; ///< Timer used to schedule periodic memory info fetching.
    int flush_msecs { 1500 }; ///< Interval in milliseconds for memory info refresh.
};

/**
 * @brief The CCIMX_AbstractMemoryInfoDriver class
 * Abstract base class for platform-specific memory information drivers.
 * Provides interface to fetch memory statistics.
 */
class CCIMX_AbstractMemoryInfoDriver {
public:
    CCIMX_AbstractMemoryInfoDriver() = default;
    virtual ~CCIMX_AbstractMemoryInfoDriver() = default;

    /**
     * @brief factory
     * Populate the MemoryStat structure with current memory info.
     * @param stat Reference to MemoryStat structure to fill.
     */
    virtual void factory(MemoryInfoFetcher::MemoryStat& stat) = 0;
};

#endif // MEMORYINFOFETCHER_H
