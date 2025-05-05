#include "CPUStateFetcher.h"
#include "platforms/PlatformDriverFactory.h"
#include <QDebug>
#include <QTimer>
CPUStateFetcher::CPUStateFetcher(QObject* parent)
	: QObject { parent } {
	/* setup accordings platform */
	setup_platform_relative();
	flush_timer.setInterval(flush_msecs);
	connect(&flush_timer, &QTimer::timeout, this, &CPUStateFetcher::flush_once);
	flush_timer.start();
}

CPUStateFetcher::~CPUStateFetcher() {
	qDebug() << "CPUStateFetcher destructor";
	delete platform_driver_base;
	flush_timer.stop();
	qDebug() << "CPUStateFetcher destructor done";
}

void CPUStateFetcher::set_capture_state(bool st) {
	st ? flush_timer.start() : flush_timer.stop();
}

void CPUStateFetcher::setup_platform_relative() {
	qDebug() << "Setup accordings to the platforms for cpu sessions";
	/* setup the driver */
	this->platform_driver_base = PlatformDriverFactory::cpustate_from_platform();
	if (!platform_driver_base) {
		qDebug() << "No platform driver found!";
	}
}

void CPUStateFetcher::flush_once() {
	/* flush the info for once */
	platform_driver_base->factory(cpustate);
#ifdef QT_DEBUG
	qDebug() << "Fetch the cpu state once: "
			 << "Idle:" << cpustate.idle
			 << "User:" << cpustate.user
			 << "Kernel:" << cpustate.kernel;
#endif
	emit flush_cpustate(cpustate);
}
