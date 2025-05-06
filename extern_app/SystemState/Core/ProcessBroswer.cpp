#include "ProcessBroswer.h"
#include "platforms/PlatformDriverFactory.h"
#include <QDebug>
ProcessBroswer::ProcessBroswer(QObject* parent)
	: QObject { parent } {

	/* setup accordings platform */
	setup_platform_relative();
	flush_timer.setInterval(flush_msecs);
	connect(&flush_timer, &QTimer::timeout, this, &ProcessBroswer::flush_once);
	flush_timer.start();
}

ProcessBroswer::~ProcessBroswer() {
	qDebug() << "ProcessBroswer destructor";
	delete platform_driver_base;
	flush_timer.stop();
	qDebug() << "ProcessBroswer destructor done";
}

void ProcessBroswer::set_capture_state(bool st) {
	st ? flush_timer.start() : flush_timer.stop();
}

void ProcessBroswer::setup_platform_relative() {
	qDebug() << "Setup accordings to the platforms for process sessions";
	/* setup the driver */
	this->platform_driver_base = PlatformDriverFactory::processdriver_from_platform();
}

void ProcessBroswer::flush_once() {
	/* flush the info for once */
	platform_driver_base->factory(process_list);
#ifdef QT_DEBUG
    // qDebug() << "Fetch the process list once: " << process_list.size();
    // for (const auto& process : std::as_const(process_list)) {
    // 	qDebug() << "PID:" << process.pid
    // 			 << "PPID:" << process.ppid
    // 			 << "Name:" << process.name
    // 			 << "FullPath:" << process.fullPath
    // 			 << "ThreadCount:" << process.threadCount
    // 			 << "MemoryUsageKB:" << process.memoryUsageKB
    // 			 << "CPUPercent:" << process.cpuPercent
    // 			 << "UserName:" << process.userName;
    // }
#endif
	emit fetch_finish(process_list);
}
