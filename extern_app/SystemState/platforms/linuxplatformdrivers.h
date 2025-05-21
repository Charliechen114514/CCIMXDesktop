#ifndef LINUXPLATFORMDRIVERS_H
#define LINUXPLATFORMDRIVERS_H

/* hence some linux platform drivers here */
#include "Core/CPUStateFetcher.h"
#include "Core/MemoryInfoFetcher.h"
#include "Core/ProcessBroswer.h"
#include <QtClassHelperMacros>

/**
 * @brief The LinuxPlatformMemoryInfoDriver class
 * provides the memory info driver
 */
class LinuxPlatformMemoryInfoDriver : public CCIMX_AbstractMemoryInfoDriver {
public:
    LinuxPlatformMemoryInfoDriver() = default;
    Q_DISABLE_COPY(LinuxPlatformMemoryInfoDriver);
    void factory(MemoryInfoFetcher::MemoryStat& memory_state) override;
};

/**
 * @brief The LinuxPlatformCPUStateDriver class
 * provides the cpu state driver
 */
class LinuxPlatformCPUStateDriver : public CCIMX_AbstractCPUStateDriver{
public:
    LinuxPlatformCPUStateDriver() = default;
    Q_DISABLE_COPY(LinuxPlatformCPUStateDriver);
    void factory(CPUStateFetcher::CPUState &state) override;
};

/**
 * @brief The LinuxPlatformProcessBrowserDriver class
 * provides the process browser driver
 */
class LinuxPlatformProcessBrowserDriver : public CCIMX_AbstractProcessBroswerDriver
{
public:
    LinuxPlatformProcessBrowserDriver() = default;
    Q_DISABLE_COPY(LinuxPlatformProcessBrowserDriver);
    void factory(QList<ProcessBroswer::ProcessInfo> &lists) override;
};

#endif // LINUXPLATFORMDRIVERS_H
