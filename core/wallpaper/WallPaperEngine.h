#ifndef WALLPAPERENGINE_H
#define WALLPAPERENGINE_H

#include <QEasingCurve>
#include <QMap>
#include <QObject>
#include <QStringList>
class QMainWindow;
class QWidget;
class QLabel;
class QTimer;
class DesktopMainWindow;

/**
 * @brief Engine managing desktop wallpaper switching and animations.
 *
 * Supports multiple switching modes such as gradient, fixed, and movement,
 * handles wallpaper image lists, animation timing, and wallpaper display.
 */
class WallPaperEngine : public QObject {
    Q_OBJECT

public:
    /**
     * @brief Enum for wallpaper switching modes.
     */
    enum class SwitchingMode {
        Gradient, ///< Wallpaper switches with gradient effect.
        Fixed, ///< Fixed wallpaper without switching.
        Movement ///< Wallpaper switches with movement animation.
    };

    /**
     * @brief Helper struct for mapping between mode names and enum values.
     */
    struct ModeMapping {
        /**
         * @brief Mapping from string names to SwitchingMode values.
         */
        const QMap<QString, WallPaperEngine::SwitchingMode> mappings = {
            { "Fixed WallPaper", SwitchingMode::Fixed },
            { "Gradient Switch", SwitchingMode::Gradient },
            { "Movement Sessions", SwitchingMode::Movement },
        };

        /**
         * @brief Returns all mode names as a QStringList.
         * @return List of mode names.
         */
        inline QStringList values() const {
            return mappings.keys();
        }

        /**
         * @brief Converts a SwitchingMode enum to its string representation.
         * @param mode The mode to convert.
         * @return Corresponding mode name.
         */
        inline QString toString(const WallPaperEngine::SwitchingMode mode) {
            return mappings.key(mode);
        }

        /**
         * @brief Converts a string name to the corresponding SwitchingMode enum.
         * @param l The mode name string.
         * @throws std::runtime_error if the name is invalid.
         * @return Corresponding SwitchingMode.
         */
        inline WallPaperEngine::SwitchingMode fromString(const QString& l) {
            auto finder = mappings.find(l);
            if (finder == mappings.end()) {
                throw std::runtime_error("Invalid Name");
            }
            return finder.value();
        }
    } modeMappings; ///< mode mappings for the string <=> mode transfer

private:
    static constexpr unsigned int SWITCH_INTERVAL = 20000; ///< Default wallpaper switch interval in ms
    static constexpr unsigned int ANIMATION_DURATION = 2000; ///< Default animation duration in ms
    static constexpr SwitchingMode DEF_MODE = SwitchingMode::Movement; ///< Default switching mode

public:
    friend class WallPaperAnimationHandler;

    /**
     * @brief Deleted default constructor.
     */
    WallPaperEngine() = delete;

    /**
     * @brief Constructs the wallpaper engine associated with a main window.
     * @param window Pointer to the main desktop window.
     */
    explicit WallPaperEngine(DesktopMainWindow* window);

    /**
     * @brief Handles resizing events, adjusting wallpaper display accordingly.
     * @param window Pointer to the main desktop window.
     */
    void process_resize(DesktopMainWindow* window);

    /**
     * @brief Sets the interval between wallpaper switches.
     * @param new_interval Interval in milliseconds.
     */
    void set_switch_interval(int new_interval);

    /**
     * @brief Gets the current wallpaper switch interval.
     * @return Interval in milliseconds.
     */
    int switch_interval() const;

    /**
     * @brief Sets the animation speed duration in milliseconds.
     * @param msspeed Duration in milliseconds.
     */
    void set_animation_speed(int msspeed) { animation_durations = msspeed; }

    /**
     * @brief Gets the current animation speed duration.
     * @return Animation duration in milliseconds.
     */
    int animation_speed() const { return animation_durations; }

    /**
     * @brief Sets the wallpaper switching mode.
     * @param mode New switching mode.
     */
    void set_mode(const SwitchingMode mode);

    /**
     * @brief Retrieves the currently displayed wallpaper pixmap.
     * @return Current wallpaper pixmap.
     */
    QPixmap get_current_pixmap() const;

    /**
     * @brief Gets the current switching mode.
     * @return Current mode.
     */
    SwitchingMode current_mode() const { return mode; }

    /**
     * @brief Sets the pixmap currently showing as wallpaper.
     * @param map Pixmap to display.
     */
    void set_showing_pictures(const QPixmap& map);

    /**
     * @brief Sets the animation duration in seconds.
     * @param secs Duration in seconds.
     */
    void set_animation_duration_second(int secs);

    /**
     * @brief Gets the animation duration in seconds.
     * @return Duration in seconds.
     */
    int duration_seconds() const;

    /**
     * @brief Returns a reference to the wallpaper image file path list.
     * @return Reference to image list.
     */
    QStringList& get_image_list();

    /**
     * @brief Sets the list of wallpaper image file paths.
     * @param l New image list.
     */
    void set_image_list(const QStringList& l);

    /**
     * @brief Resets all settings to default values.
     */
    void reset_defaults();
    /**
     * @brief get_easingcurve
     * @return
     */
    QEasingCurve get_easingcurve() const;

    /**
     * @brief set_easingcurve
     * @param curveType set as curveType indicates
     */
    void set_easingcurve(const QEasingCurve curveType);

    /**
     * @brief Handles fallback behavior when no wallpaper images are available.
     */
    void fallback_empty_session();

signals:
    /**
     * @brief Signal emitted when the wallpaper image list changes.
     * @param l New image list.
     */
    void imagelist_changed(const QStringList& l);

    /**
     * @brief Signal emitted when the wallpaper pixmap changes.
     * @param pixmap New wallpaper pixmap.
     */
    void wallpaperChanged(const QPixmap& pixmap);

private:
    QWidget* shoule_be_lower; ///< Widget to be placed behind wallpaper animations, usually the central widget
    QLabel* wallpaperLabel { nullptr }; ///< Label to display the current wallpaper
    QLabel* bufferpaperLabel { nullptr }; ///< Label used as buffer for animations
    QTimer* invoke_switch_timer; ///< Timer controlling wallpaper switching intervals
    QStringList image_lists; ///< List of wallpaper image file paths

    /**
     * @brief Internal method triggered by timer to switch wallpaper.
     */
    void process_internal_timer_hook();

    /**
     * @brief Runs default operations when flushing wallpaper state.
     */
    void default_behaviour_of_flush();

    SwitchingMode mode { DEF_MODE }; ///< Current wallpaper switching mode
    int animation_durations { ANIMATION_DURATION }; ///< Duration of animation in milliseconds
    QEasingCurve curve { QEasingCurve::InOutCubic }; // current curse;
};

#endif // WALLPAPERENGINE_H
