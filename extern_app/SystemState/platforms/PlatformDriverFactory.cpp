#include "PlatformDriverFactory.h"
#include <QtGlobal>
#ifdef Q_OS_WIN
#include "platforms/Win32PlatformDrivers.h"
#else
#include "platforms/linuxplatformdrivers.h"
#endif

CCIMX_AbstractMemoryInfoDriver* PlatformDriverFactory::
	meminfo_from_platform() {
#ifdef Q_OS_WIN
	return new Win32PlatformMemoryInfoDriver();
#else
    return new LinuxPlatformMemoryInfoDriver();
#endif
}

CCIMX_AbstractCPUStateDriver* PlatformDriverFactory::
	cpustate_from_platform() {
#ifdef Q_OS_WIN
	return new Win32PlatformCPUStateDriver();
#else
    return new LinuxPlatformCPUStateDriver();
#endif
}

CCIMX_AbstractProcessBroswerDriver* PlatformDriverFactory::
	processdriver_from_platform() {
#ifdef Q_OS_WIN
	return new Win32PlatformProcessBroswerDriver();
#else
    return new LinuxPlatformProcessBrowserDriver();
#endif
}
