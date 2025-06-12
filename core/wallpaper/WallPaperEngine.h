#ifndef WALLPAPERENGINE_H
#define WALLPAPERENGINE_H
#include <QObject>
#include <QStringList>
class QMainWindow;
class QWidget;
class QLabel;
class QTimer;
class DesktopMainWindow;
class WallPaperEngine : public QObject {
public:
    enum class SwitchingMode {
        Gradient,
        Fixed
    };

private:
    Q_OBJECT
    static constexpr unsigned int SWITCH_INTERVAL = 20000;
    static constexpr SwitchingMode DEF_MODE = SwitchingMode::Gradient;

public:
    friend class WallPaperAnimationHandler;
    WallPaperEngine() = delete;
    explicit WallPaperEngine(DesktopMainWindow* window);
    void process_resize(DesktopMainWindow* window);
    void set_switch_interval(int new_interval);
    int switch_interval() const;
    void set_mode(const SwitchingMode mode);
    void set_showing_pictures(const QString& path);
    QStringList& get_image_list();
    void set_image_list(const QStringList& l);
    void reset_defaults();
    void fallback_empty_session();
signals:
    void imagelist_changed(const QStringList& l);

private:
    QWidget* shoule_be_lower; ///< Widget that should be placed behind animations, typically the central widget
    QLabel* wallpaperLabel { nullptr }; ///< Displays current wallpaper
    QLabel* bufferpaperLabel { nullptr }; ///< Used for animation buffering
    QTimer* invoke_switch_timer; ///< Timer to control wallpaper switching intervals
    QStringList image_lists; ///< List of wallpaper image paths
    void process_internal_timer_hook(); ///< Trigger wallpaper page switch session
    void default_behaviour_of_flush();
    SwitchingMode mode { DEF_MODE }; ///< default wallpaper mode
};

#endif // WALLPAPERENGINE_H
