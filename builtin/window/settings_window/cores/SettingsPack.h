#ifndef SETTINGSPACK_H
#define SETTINGSPACK_H

#include "core/wallpaper/WallPaperEngine.h"
#include <QColor>
#include <QEasingCurve>
#include <QFont>
#include <QPixmap>
/**
 * @brief The AppWidgetsSettingsInfoPack struct
 * Stores configuration parameters for AppWidget appearance.
 */
struct AppWidgetsSettingsInfoPack {
    QColor fontColor; ///< Text color for the widget.
    QFont font; ///< Font used by the widget.
    int iconSize; ///< Size of the icon displayed.
};

/**
 * @brief The BaseWallPaperSettings class
 * Abstract base for wallpaper configuration settings.
 */
struct BaseWallPaperSettings {
public:
    /**
     * @brief Types of wallpaper switching behaviors.
     */
    enum class Type {
        FIXED, ///< Fixed image wallpaper.
        FLOW_LIKE ///< Sequential image switching.
    };

    /**
     * @brief Constructor with type.
     * @param t Wallpaper type.
     */
    BaseWallPaperSettings(const Type t)
        : type(t) { }

    BaseWallPaperSettings() = delete;
    virtual ~BaseWallPaperSettings() = default;

    /**
     * @brief Gets the wallpaper type.
     * @return Type of the wallpaper.
     */
    Type get_type() const { return type; }

private:
    const Type type; ///< Internal type.
};

/**
 * @brief The FixedTypeWallPaperSettings struct
 * Settings for fixed image wallpaper display.
 */
struct FixedTypeWallPaperSettings : public BaseWallPaperSettings {
    FixedTypeWallPaperSettings()
        : BaseWallPaperSettings(BaseWallPaperSettings::Type::FIXED) {
    }

    QPixmap map; ///< The fixed wallpaper image.
    WallPaperEngine::SwitchingMode mode; ///< Switching mode (though unused for fixed).
};

/**
 * @brief The FlowTypeTypeWallPaperSettings struct
 * Settings for flow-like (sequentially switched) wallpapers.
 */
struct FlowTypeTypeWallPaperSettings : public BaseWallPaperSettings {
    FlowTypeTypeWallPaperSettings()
        : BaseWallPaperSettings(BaseWallPaperSettings::Type::FLOW_LIKE) {
    }
    QEasingCurve curve; ///< curve type for animations
    QStringList images; ///< List of images to switch between.
    int animation_speed; ///< Transition animation speed (ms).
    int switch_interval; ///< Interval between switches (ms).
    WallPaperEngine::SwitchingMode mode; ///< Switching mode behavior.
};

#endif // SETTINGSPACK_H
