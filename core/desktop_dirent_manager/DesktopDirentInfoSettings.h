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
    PLUGIN_WIDGET_PLACED, ///< plugins places
};

static constexpr const char* DesktopServerTypeMETAS[] = {
    "Toast Summon"
    "Plugin Widget Placed"
};

static constexpr unsigned short
    DesktopServerTypeMAX
    = static_cast<unsigned short>(DesktopServerType::PLUGIN_WIDGET_PLACED) + 1;

static constexpr const char* TOAST_SUMMON_DIRENT = ".__toast_summon_dirent";
static constexpr const char* PLUGIN_WIDGET_PLACED = "plugins";

enum class ConfigureFileName {
    UserConfig
};

static constexpr unsigned short
    ConfigureFileNameMAX
    = static_cast<unsigned short>(ConfigureFileName::UserConfig) + 1;

static constexpr std::pair<const char*, const char*>
    configs_dirent_name_pair[] {
        // using as dirent in config sub, config name
        { ".", "user_config.json" }
    };

static_assert(
    sizeof(configs_dirent_name_pair) / sizeof(configs_dirent_name_pair[0])
        == ConfigureFileNameMAX,
    "configs_dirent_name_pair and Enums are count mismatched!");

#endif // DESKTOPDIRENTINFOSETTINGS_H
