#ifndef DESKTOPDIRENTINFOSETTINGS_H
#define DESKTOPDIRENTINFOSETTINGS_H
#include <QString>
enum class DesktopDirentType : short {
    Documents, ///< Documents folder
    Downloads, ///< Downloads folder
    Music, ///< Music folder
    Pictures, ///< Pictures folder
    Videos, ///< Videos folder
    Binaries, ///< binaries folder contains
    Config, ///< Configuration files (e.g. .config on Linux)
    Cache, ///< Cached data directory
    Runtime, ///< Runtime or temporary files
    Trash, ///< Recycle bin / Trash
};

/**
 * @brief Meta infos
 */
static constexpr const char* DesktopDirentTypeMETAS[] = {
    "Documentations", "Downloads", "Music", "Pictures",
    "Videos", "Binaries", "Config", "Cache", "Runtime", "Trash"
};

static constexpr unsigned short
    DesktopDirentTypeMAX
    = static_cast<unsigned short>(DesktopDirentType::Trash) + 1;

static_assert(
    sizeof(DesktopDirentTypeMETAS) / sizeof(DesktopDirentTypeMETAS[0])
        == DesktopDirentTypeMAX,
    "DesktopServerDirentMetas and Enums are count mismatched!");

enum class DesktopServerType {
    TOAST_SUMMON, ///< place where toast summons, which we will monitors
    PLUGIN_WIDGET_PLACED
};

static constexpr const char* DesktopServerTypeMETAS[] = {
    "Toast Summon"
    "Plugin Widget Placed"
};

static constexpr unsigned short
    DesktopServerTypeMAX
    = static_cast<unsigned short>(DesktopServerType::TOAST_SUMMON) + 1;

static_assert(
    sizeof(DesktopServerTypeMETAS) / sizeof(DesktopServerTypeMETAS[0])
        == DesktopServerTypeMAX,
    "DesktopServerTypeMETAS and Enums are count mismatched!");

static constexpr const char* TOAST_SUMMON_DIRENT = ".__toast_summon_dirent";
static constexpr const char* PLUGIN_WIDGET_PLACED = "plugins";
#endif // DESKTOPDIRENTINFOSETTINGS_H
