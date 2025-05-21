#ifndef PROCESSBROSWER_H
#define PROCESSBROSWER_H
#include <QObject>
#include <QTimer>
class CCIMX_AbstractProcessBroswerDriver;

/**
 * @brief The ProcessBroswer class
 * @details ProcessBroswer is the process broswer provides
 * the process information
 */
class ProcessBroswer : public QObject {
	Q_OBJECT
public:
	explicit ProcessBroswer(QObject* parent = nullptr);
	~ProcessBroswer();

	/**
	 * @brief The ProcessInfo class
	 * @details ProcessInfo is the process information
	 */
	struct ProcessInfo {
		int pid; ///< the process id
		int ppid; ///< the parent process id
		QString name; ///< the process name
		QString fullPath; ///< the full path of the process
		int threadCount; ///< the thread count of the process
		qint64 memoryUsageKB; ///< the memory usage of the process in KB level
		double cpuPercent; ///< the cpu percent of the process
		QString userName; ///< the user name of the process
	};
	/* interface is expected to set the freq of the flush */

	/**
	 * @brief set_flush_freq
	 * set the flush frequency in msec times
	 * @param msecs the msecs to set
	 */
	void set_flush_freq(const int msecs) { flush_msecs = msecs; }

	/**
	 * @brief set_capture_state
	 * @param st the state to set
	 */
	void set_capture_state(bool st);
signals:
	/**
	 * @brief about_fetch_process the signal indicating the process is ready
	 * @param infos the process information
	 */
	void fetch_finish(const QList<ProcessBroswer::ProcessInfo>& infos);

private:
	CCIMX_AbstractProcessBroswerDriver* platform_driver_base { nullptr };
	void setup_platform_relative();
	/* this is used to flush the cpu state */
	void flush_once();
	int flush_msecs { 1500 };
	QList<ProcessInfo> process_list;
	QTimer flush_timer;
};

/**
 * @brief The CCIMX_AbstractProcessBroswerDriver class
 * @details CCIMX_AbstractProcessBroswerDriver is the abstract class
 * for the process broswer driver
 */
class CCIMX_AbstractProcessBroswerDriver {
public:
	CCIMX_AbstractProcessBroswerDriver() = default;
	virtual ~CCIMX_AbstractProcessBroswerDriver() = default;
	/* driver is expected to make a stat back, locating in platforms */
	virtual void factory(QList<ProcessBroswer::ProcessInfo>& lists) = 0;
};

#endif // PROCESSBROSWER_H
