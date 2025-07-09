#ifndef MEMORYSTATEQUERY_H
#define MEMORYSTATEQUERY_H
#include <cstdint>
namespace MemoryState {

/**
 * @brief The MemState class records the type of the
 * memories
 */
struct MemState {
    uint64_t total_phys_memory; ///< Total physical memory in bytes.
    uint64_t avail_phys_memory; ///< Available physical memory in bytes.
    uint64_t total_virt_memory; ///< Total virtual memory in bytes.
    uint64_t avail_virt_memory; ///< Available virtual memory in bytes.
};

MemState queryOnce();

};

#endif // MEMORYSTATEQUERY_H
