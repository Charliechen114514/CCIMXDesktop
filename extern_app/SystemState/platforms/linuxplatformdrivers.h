#ifndef LINUXPLATFORMDRIVERS_H
#define LINUXPLATFORMDRIVERS_H

/* Some Linux platform drivers here */
#include "Core/CPUStateFetcher.h"
#include "Core/MemoryInfoFetcher.h"
#include "Core/ProcessBroswer.h"
#include <QtClassHelperMacros>

/**
 * @brief The LinuxPlatformMemoryInfoDriver class provides the memory info driver for Linux.
 */
class LinuxPlatformMemoryInfoDriver : public CCIMX_AbstractMemoryInfoDriver {
public:
    LinuxPlatformMemoryInfoDriver() = default;
    /**
     * @brief disable copy
     */
    Q_DISABLE_COPY(LinuxPlatformMemoryInfoDriver);
    /**
     * @brief Factory method to get memory stats.
     * @param memory_state Reference to MemoryInfoFetcher::MemoryStat to store stats.
     */
    void factory(MemoryInfoFetcher::MemoryStat& memory_state) override;
};

/**
 * @brief The LinuxPlatformCPUStateDriver class provides the CPU state driver for Linux.
 */
class LinuxPlatformCPUStateDriver : public CCIMX_AbstractCPUStateDriver {
public:
    LinuxPlatformCPUStateDriver() = default;
    /**
     * @brief disable copy
     */
    Q_DISABLE_COPY(LinuxPlatformCPUStateDriver);
    /**
     * @brief Factory method to get CPU state.
     * @param state Reference to CPUStateFetcher::CPUState to store stats.
     */
    void factory(CPUStateFetcher::CPUState& state) override;
};

/**
 * @brief The LinuxPlatformProcessBrowserDriver class provides the process browser driver for Linux.
 */
class LinuxPlatformProcessBrowserDriver : public CCIMX_AbstractProcessBroswerDriver {
public:
    LinuxPlatformProcessBrowserDriver() = default;
    /**
     * @brief disable copy
     */
    Q_DISABLE_COPY(LinuxPlatformProcessBrowserDriver);
    /**
     * @brief Factory method to get process information list.
     * @param lists Reference to QList of ProcessBroswer::ProcessInfo to store process info.
     */
    void factory(QList<ProcessBroswer::ProcessInfo>& lists) override;
};

#endif // LINUXPLATFORMDRIVERS_H
