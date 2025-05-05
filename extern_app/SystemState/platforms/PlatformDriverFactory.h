#ifndef PLATFORMDRIVERFACTORY_H
#define PLATFORMDRIVERFACTORY_H
#include <QtClassHelperMacros>
class CCIMX_AbstractMemoryInfoDriver;
class CCIMX_AbstractCPUStateDriver;
class CCIMX_AbstractProcessBroswerDriver;
class PlatformDriverFactory {
public:
	PlatformDriverFactory() = default;
	Q_DISABLE_COPY(PlatformDriverFactory);
	static CCIMX_AbstractMemoryInfoDriver* meminfo_from_platform();
	static CCIMX_AbstractCPUStateDriver* cpustate_from_platform();
	static CCIMX_AbstractProcessBroswerDriver* processdriver_from_platform();
};

#endif // PLATFORMDRIVERFACTORY_H
