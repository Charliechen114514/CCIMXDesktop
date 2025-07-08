#ifndef DISKUSAGE_H
#define DISKUSAGE_H
#include <cstdint>
namespace DiskUsage {
struct MetaInfo {
    uint64_t total;
    uint64_t free;
    uint64_t available;
};

MetaInfo queryOnce();
};

#endif // DISKUSAGE_H
