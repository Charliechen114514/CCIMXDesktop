/**
 * @file DiskUsage.h
 * @brief Defines structures and functions for querying disk usage information.
 */

#ifndef DISKUSAGE_H
#define DISKUSAGE_H

#include <cstdint> // For fixed-width integer types like uint64_t

/**
 * @namespace DiskUsage
 * @brief Provides utilities for querying disk space information.
 *
 * This namespace encapsulates functionalities related to retrieving
 * details about disk partitions or file systems, such as total space,
 * free space, and available space.
 */
namespace DiskUsage {

/**
 * @struct MetaInfo
 * @brief Represents metadata about disk space.
 *
 * This structure holds various metrics related to disk usage, typically
 * for a specific mounted file system or disk partition. All values are
 * expected to be in bytes.
 */
struct MetaInfo {
    uint64_t total; ///< Total capacity of the disk or file system in bytes.
    uint64_t free; ///< Total free space on the disk or file system in bytes. This might include space only accessible by root.
    uint64_t available; ///< Available space on the disk or file system in bytes for non-privileged users.
};

/**
 * @brief Queries the disk usage information for a default or currently active partition/drive.
 *
 * This function retrieves a snapshot of the disk's total, free, and available space.
 * The specific disk or partition queried might depend on the operating system's
 * default behavior or an internal configuration not exposed in this header.
 * @return A `MetaInfo` structure containing the queried disk usage details.
 */
MetaInfo queryOnce();

} // namespace DiskUsage

#endif // DISKUSAGE_H
