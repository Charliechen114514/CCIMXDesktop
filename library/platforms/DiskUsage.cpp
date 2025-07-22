// #include "DiskUsage.h"
// #include <filesystem>
// #include <vector>
// #if defined(_WIN32)
// #include <windows.h>
// #elif defined(__linux__)
// #include <mntent.h>
// #include <sys/statvfs.h>
// #endif

// namespace fs = std::filesystem;

// namespace {
// std::vector<std::string> list_mount_points() {
//     std::vector<std::string> result;

// #if defined(_WIN32)
//     DWORD drives = GetLogicalDrives();
//     for (char letter = 'A'; letter <= 'Z'; ++letter) {
//         if (drives & (1 << (letter - 'A'))) {
//             std::string path = std::string(1, letter) + ":\\";
//             result.push_back(path);
//         }
//     }
// #elif defined(__linux__)
//     FILE* fp = setmntent("/proc/mounts", "r");
//     if (!fp)
//         return result;

//     struct mntent* ent;
//     while ((ent = getmntent(fp)) != nullptr) {
//         std::string fsname = ent->mnt_fsname;
//         if (fsname.find("/dev/") == 0) { // 排除 pseudo filesystems
//             result.push_back(ent->mnt_dir);
//         }
//     }
//     endmntent(fp);
// #endif

//     return result;
// }
// }

// DiskUsage::MetaInfo DiskUsage::queryOnce() {
//     std::vector<DiskUsage::MetaInfo> infos;
//     for (const auto& mount : list_mount_points()) {
//         auto space = fs::space(mount);
//         infos.push_back(DiskUsage::MetaInfo {
//             space.capacity,
//             space.free,
//             space.available });
//     }
//     DiskUsage::MetaInfo result {};
//     for (const auto& each : infos) {
//         result.available += each.available;
//         result.free += each.free;
//         result.total += each.total;
//     }

//     return result;
// }

#include "DiskUsage.h"
#include <filesystem>
#include <vector>

#if defined(_WIN32)
#include <windows.h>
#elif defined(__linux__)
#include <mntent.h>
#include <sys/statvfs.h>
#endif

namespace fs = std::filesystem;

namespace {

// 判断是否为伪文件系统（仅用于 Linux）
#if defined(__linux__)
bool isPseudoFs(const std::string& type) {
    static const std::vector<std::string> pseudoTypes = {
        "proc", "sysfs", "tmpfs", "devtmpfs", "devpts", "cgroup", "cgroup2",
        "securityfs", "pstore", "autofs", "debugfs", "mqueue", "overlay",
        "tracefs", "nsfs", "configfs", "rpc_pipefs"
    };
    for (const auto& t : pseudoTypes) {
        if (type == t)
            return true;
    }
    return false;
}
#endif

std::vector<std::string> list_mount_points() {
    std::vector<std::string> result;

#if defined(_WIN32)
    DWORD drives = GetLogicalDrives();
    for (char letter = 'A'; letter <= 'Z'; ++letter) {
        if (drives & (1 << (letter - 'A'))) {
            std::string path = std::string(1, letter) + ":\\";
            result.push_back(path);
        }
    }
#elif defined(__linux__)
    FILE* fp = setmntent("/proc/mounts", "r");
    if (!fp)
        return result;

    struct mntent* ent;
    while ((ent = getmntent(fp)) != nullptr) {
        std::string mountDir = ent->mnt_dir;
        std::string fsType   = ent->mnt_type;

        if (!isPseudoFs(fsType)) {
            result.push_back(mountDir);
        }
    }

    endmntent(fp);
#endif

    return result;
}

} // end anonymous namespace

DiskUsage::MetaInfo DiskUsage::queryOnce() {
    std::vector<DiskUsage::MetaInfo> infos;
    for (const auto& mount : list_mount_points()) {
        std::error_code ec;
        auto space = fs::space(mount, ec);
        if (!ec) {
            infos.push_back(DiskUsage::MetaInfo {
                space.capacity,
                space.free,
                space.available
            });
        }
    }

    DiskUsage::MetaInfo result {};
    for (const auto& each : infos) {
        result.available += each.available;
        result.free     += each.free;
        result.total    += each.total;
    }

    return result;
}

