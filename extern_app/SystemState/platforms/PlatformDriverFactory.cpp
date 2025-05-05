#include "PlatformDriverFactory.h"
#include <QtGlobal>
#ifdef Q_OS_WIN
#include "platforms/Win32PlatformDrivers.h"
#else

#endif

CCIMX_AbstractMemoryInfoDriver* PlatformDriverFactory::
	meminfo_from_platform() {
#ifdef Q_OS_WIN
	return new Win32PlatformMemoryInfoDriver();
#else
	return nullptr;
#endif
}

CCIMX_AbstractCPUStateDriver* PlatformDriverFactory::
	cpustate_from_platform() {
#ifdef Q_OS_WIN
	return new Win32PlatformCPUStateDriver();
#else
	return nullptr;
#endif
}

CCIMX_AbstractProcessBroswerDriver* PlatformDriverFactory::
	processdriver_from_platform() {
#ifdef Q_OS_WIN
	return new Win32PlatformProcessBroswerDriver();
#else
	return nullptr;
#endif
}
