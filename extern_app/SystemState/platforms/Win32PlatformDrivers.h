#ifndef WIN32PLATFORMDRIVERS_H
#define WIN32PLATFORMDRIVERS_H

#include "Core/CPUStateFetcher.h"
#include "Core/MemoryInfoFetcher.h"
#include "Core/ProcessBroswer.h"
#include <QtClassHelperMacros>
#include <windows.h>

/**
 * @brief The Win32PlatformMemoryInfoDriver class provides the memory info driver
 */
class Win32PlatformMemoryInfoDriver : public CCIMX_AbstractMemoryInfoDriver {
public:
	Win32PlatformMemoryInfoDriver() = default;
	/**  
	 * @brief disable copy sessions 
	 */
	Q_DISABLE_COPY(Win32PlatformMemoryInfoDriver);
	/**
	 * @brief Factory method to get memory stats
	 * @param stat Reference to MemoryInfoFetcher::MemoryStat to store stats
	 */
	void factory(MemoryInfoFetcher::MemoryStat& stat) override;
};

/**
 * @brief The Win32PlatformCPUStateDriver class provides the CPU state driver
 */
class Win32PlatformCPUStateDriver : public CCIMX_AbstractCPUStateDriver {
public:
	Win32PlatformCPUStateDriver() = default;
	/**  
	 * @brief disable copy sessions 
	 */
	Q_DISABLE_COPY(Win32PlatformCPUStateDriver);
	/**
	 * @brief Factory method to get CPU state
	 * @param stat Reference to CPUStateFetcher::CPUState to store stats
	 */
	void factory(CPUStateFetcher::CPUState& stat) override;
};

/**
 * @brief The Win32PlatformProcessBroswerDriver class provides the process browser driver
 */
class Win32PlatformProcessBroswerDriver : public CCIMX_AbstractProcessBroswerDriver {
public:
	Win32PlatformProcessBroswerDriver() = default;
	/**  
	 * @brief disable copy sessions 
	 */
	Q_DISABLE_COPY(Win32PlatformProcessBroswerDriver);
	/**
	 * @brief Factory method to get process information list
	 * @param lists Reference to QList of ProcessBroswer::ProcessInfo to store info
	 */
	void factory(QList<ProcessBroswer::ProcessInfo>& lists) override;
};

#endif // WIN32PLATFORMDRIVERS_H
