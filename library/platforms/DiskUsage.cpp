#include "DiskUsage.h"
#include <filesystem>

#if defined(_WIN32)
#include <windows.h>
#elif defined(__linux__)
#include <mntent.h>
#include <sys/statvfs.h>
#endif

namespace fs = std::filesystem;

namespace {
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
        std::string fsname = ent->mnt_fsname;
        if (fsname.find("/dev/") == 0) { // 排除 pseudo filesystems
            result.push_back(ent->mnt_dir);
        }
    }
    endmntent(fp);
#endif

    return result;
}
}

DiskUsage::MetaInfo DiskUsage::queryOnce() {
    std::vector<DiskUsage::MetaInfo> infos;
    for (const auto& mount : list_mount_points()) {
        auto space = fs::space(mount);
        infos.push_back(DiskUsage::MetaInfo {
            space.capacity,
            space.free,
            space.available });
    }
    DiskUsage::MetaInfo result {};
    for (const auto& each : infos) {
        result.available += each.available;
        result.free += each.free;
        result.total += each.total;
    }

    return result;
}
