#ifndef MEMORYINFOFETCHER_H
#define MEMORYINFOFETCHER_H

#include <QObject>
#include <QTimer>
/* pre-announcement of the dirver */
class CCIMX_AbstractMemoryInfoDriver;
/*
 * Memory Info fetcher is a class that
 */
class MemoryInfoFetcher : public QObject {
	Q_OBJECT
public:
	static QString format_size(quint64 size);
	explicit MemoryInfoFetcher(QObject* parent = nullptr);
	Q_DISABLE_COPY(MemoryInfoFetcher);
	~MemoryInfoFetcher();
	struct MemoryStat {
		/* Bytes level count */
		quint64 total_phys_memory;
		quint64 avail_phys_memory;
		quint64 total_virt_memory;
		quint64 avail_virt_memory;
	} mem_stat;
	/* interface is expected to set the freq of the flush */
	void set_flush_freq(const int msecs) { flush_msecs = msecs; }
	void set_capture_state(bool st);
signals:
	void finish_detect_memory(const MemoryInfoFetcher::MemoryStat&);
private slots:
	/* invoke this make a interactive with driver */
	void flush_once();

private:
	CCIMX_AbstractMemoryInfoDriver* platform_driver_base { nullptr };
	void setup_platform_relative();
	QTimer flush_timer;
	int flush_msecs { 1500 };
};

/*
 *  This is a abstract class that is used to being as a base class
 *  for the driver in different platforms
 */
class CCIMX_AbstractMemoryInfoDriver {
public:
	CCIMX_AbstractMemoryInfoDriver() = default;
	virtual ~CCIMX_AbstractMemoryInfoDriver() = default;
	/* driver is expected to make a stat back, locating in platforms */
	virtual void factory(MemoryInfoFetcher::MemoryStat&) = 0;
};

#endif // MEMORYINFOFETCHER_H
