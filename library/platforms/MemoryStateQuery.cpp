#include "MemoryStateQuery.h"

#ifdef _WIN32
#include <Windows.h>
void from_platform(MemoryState::MemState& stat) {
    MEMORYSTATUSEX memInfo;
    memInfo.dwLength = sizeof(MEMORYSTATUSEX);
    GlobalMemoryStatusEx(&memInfo);

    /* Thus make the adaptions here */
    stat.total_phys_memory = static_cast<uint64_t>(memInfo.ullTotalPhys);
    stat.total_virt_memory = static_cast<uint64_t>(memInfo.ullTotalVirtual);
    stat.avail_virt_memory = static_cast<uint64_t>(memInfo.ullAvailVirtual);
    stat.avail_phys_memory = static_cast<uint64_t>(memInfo.ullAvailPhys);
}

#else
#include <sstream>
#include <string>
#include <unordered_map>
#include <fstream>
void from_platform(MemoryState::MemState& mem_stat) {
    std::ifstream meminfo("/proc/meminfo");
    std::string line;
    std::unordered_map<std::string, uint64_t> mem;

    while (std::getline(meminfo, line)) {
        std::istringstream iss(line);
        std::string key;
        uint64_t value;
        std::string unit;
        iss >> key >> value >> unit;
        if (!key.empty() && key.back() == ':')
            key.pop_back();
        mem[key] = value; // 单位是 kB
    }

    mem_stat.total_phys_memory = mem["MemTotal"] * 1024;
    mem_stat.avail_phys_memory = mem["MemAvailable"] * 1024;

    uint64_t swap_total = mem.count("SwapTotal") ? mem["SwapTotal"] * 1024 : 0;
    uint64_t swap_free = mem.count("SwapFree") ? mem["SwapFree"] * 1024 : 0;

    mem_stat.total_virt_memory = mem_stat.total_phys_memory + swap_total;
    mem_stat.avail_virt_memory = mem_stat.avail_phys_memory + swap_free;
}
#endif

MemoryState::MemState MemoryState::queryOnce() {
    MemoryState::MemState state;
    from_platform(state);
    return state;
}
