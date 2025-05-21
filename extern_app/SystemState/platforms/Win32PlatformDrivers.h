#ifndef WIN32PLATFORMDRIVERS_H
#define WIN32PLATFORMDRIVERS_H
#include "Core/CPUStateFetcher.h"
#include "Core/MemoryInfoFetcher.h"
#include "Core/ProcessBroswer.h"
#include <QtClassHelperMacros>
#include <windows.h>

/**
 * @brief The Win32PlatformMemoryInfoDriver class
 * provides the memory info driver
 */
class Win32PlatformMemoryInfoDriver : public CCIMX_AbstractMemoryInfoDriver {
public:
	Win32PlatformMemoryInfoDriver() = default;
	Q_DISABLE_COPY(Win32PlatformMemoryInfoDriver);
	void factory(MemoryInfoFetcher::MemoryStat& stat) override;
};

/**
 * @brief The Win32PlatformCPUStateDriver class
 * provides the CPU state driver
 */
class Win32PlatformCPUStateDriver : public CCIMX_AbstractCPUStateDriver {
public:
	Win32PlatformCPUStateDriver() = default;
	Q_DISABLE_COPY(Win32PlatformCPUStateDriver);
	void factory(CPUStateFetcher::CPUState& stat) override;
};

/**
 * @brief The Win32PlatformProcessBroswerDriver class
 * provides the process broswer driver
 */
class Win32PlatformProcessBroswerDriver : public CCIMX_AbstractProcessBroswerDriver {
public:
	Win32PlatformProcessBroswerDriver() = default;
	Q_DISABLE_COPY(Win32PlatformProcessBroswerDriver);
	void factory(QList<ProcessBroswer::ProcessInfo>& lists) override;
};

#endif // WIN32PLATFORMDRIVERS_H
