#ifndef LINUXPLATFORMDRIVERS_H
#define LINUXPLATFORMDRIVERS_H

/* hence some linux platform drivers here */
#include "Core/CPUStateFetcher.h"
#include "Core/MemoryInfoFetcher.h"
#include "Core/ProcessBroswer.h"
#include <QtClassHelperMacros>

class LinuxPlatformMemoryInfoDriver : public CCIMX_AbstractMemoryInfoDriver {
public:
    LinuxPlatformMemoryInfoDriver() = default;
    Q_DISABLE_COPY(LinuxPlatformMemoryInfoDriver);
    void factory(MemoryInfoFetcher::MemoryStat& memory_state) override;
};

class LinuxPlatformCPUStateDriver : public CCIMX_AbstractCPUStateDriver{
public:
    LinuxPlatformCPUStateDriver() = default;
    Q_DISABLE_COPY(LinuxPlatformCPUStateDriver);
    void factory(CPUStateFetcher::CPUState &state) override;
};

class LinuxPlatformProcessBrowserDriver : public CCIMX_AbstractProcessBroswerDriver
{
public:
    LinuxPlatformProcessBrowserDriver() = default;
    Q_DISABLE_COPY(LinuxPlatformProcessBrowserDriver);
    void factory(QList<ProcessBroswer::ProcessInfo> &lists) override;
};

#endif // LINUXPLATFORMDRIVERS_H
