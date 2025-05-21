#ifndef MEMORYINFOFETCHER_H
#define MEMORYINFOFETCHER_H

#include <QObject>
#include <QTimer>
/* pre-announcement of the dirver */
class CCIMX_AbstractMemoryInfoDriver;

/**
 * @brief The MemoryInfoFetcher class provides the memory information
 * @note this is the memory information fetcher
 */
class MemoryInfoFetcher : public QObject {
	Q_OBJECT
public:
	static QString format_size(quint64 size);
	explicit MemoryInfoFetcher(QObject* parent = nullptr);
	Q_DISABLE_COPY(MemoryInfoFetcher);
	~MemoryInfoFetcher();

	/**
	 * @brief The MemoryStat class provides the memory information
	 */
	struct MemoryStat {
		/* Bytes level count */
		quint64 total_phys_memory; ///< total physical memory, bytes level
		quint64 avail_phys_memory; ///< available physical memory, bytes level
		quint64 total_virt_memory; ///< total virtual memory, bytes level
		quint64 avail_virt_memory; ///< available virtual memory, bytes level
	} mem_stat;
	/* interface is expected to set the freq of the flush */

	/**
	 * @brief set_flush_freq set the flush frequency
	 * @param msecs the msecs to flush
	 */
	void set_flush_freq(const int msecs) { flush_msecs = msecs; }

	/**
	 * @brief set_capture_state set the capture state
	 * @param st the state to set, true means capture, false means not
	 */
	void set_capture_state(bool st);
signals:
	/**
	 * @brief finish_detect_memory the signal to finish the memory detection
	 * @param mem_stat the memory information carried in signals
	 */
	void finish_detect_memory(const MemoryInfoFetcher::MemoryStat&);
private slots:
	/**
	 * @brief flush_memory_info flush the memory information
	 * @note this will be called to make a interactive with driver
	 *
	 */
	void flush_once();

private:
	CCIMX_AbstractMemoryInfoDriver* platform_driver_base { nullptr };
	void setup_platform_relative();
	QTimer flush_timer;
	int flush_msecs { 1500 };
};

/**
 * @brief The CCIMX_AbstractMemoryInfoDriver class
 * provides the abstract class for the memory information driver
 * @note This is a abstract class that is used to being as a base class
 * for the driver in different platforms
 */
class CCIMX_AbstractMemoryInfoDriver {
public:
	CCIMX_AbstractMemoryInfoDriver() = default;
	virtual ~CCIMX_AbstractMemoryInfoDriver() = default;
	/* driver is expected to make a stat back, locating in platforms */
	virtual void factory(MemoryInfoFetcher::MemoryStat&) = 0;
};

#endif // MEMORYINFOFETCHER_H
