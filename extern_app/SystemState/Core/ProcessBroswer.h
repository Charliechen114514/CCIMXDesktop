#ifndef PROCESSBROSWER_H
#define PROCESSBROSWER_H
#include <QObject>
#include <QTimer>
class CCIMX_AbstractProcessBroswerDriver;

class ProcessBroswer : public QObject {
	Q_OBJECT
public:
	explicit ProcessBroswer(QObject* parent = nullptr);
	~ProcessBroswer();
	struct ProcessInfo {
		int pid;
		int ppid;
		QString name;
		QString fullPath;
		int threadCount;
		qint64 memoryUsageKB;
		double cpuPercent;
		QString userName;
	};
	/* interface is expected to set the freq of the flush */
	void set_flush_freq(const int msecs) { flush_msecs = msecs; }
	void set_capture_state(bool st);
signals:
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

class CCIMX_AbstractProcessBroswerDriver {
public:
	CCIMX_AbstractProcessBroswerDriver() = default;
	virtual ~CCIMX_AbstractProcessBroswerDriver() = default;
	/* driver is expected to make a stat back, locating in platforms */
	virtual void factory(QList<ProcessBroswer::ProcessInfo>& lists) = 0;
};

#endif // PROCESSBROSWER_H
