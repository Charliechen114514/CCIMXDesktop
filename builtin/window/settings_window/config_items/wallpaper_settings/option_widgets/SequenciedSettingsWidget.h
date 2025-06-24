#ifndef SEQUENCIEDSETTINGSWIDGET_H
#define SEQUENCIEDSETTINGSWIDGET_H

#include <QEasingCurve>
#include <QWidget>

class ImageListViewer;

namespace Ui {
class SequenciedSettingsWidget;
}

/**
 * @brief The SequenciedSettingsWidget class
 * Manages and configures a list of sequentially changing images (e.g., slideshow).
 *
 * This widget provides options to control animation duration, switching interval,
 * and manage the list of images used in rotation. It supports interaction with an external
 * image viewer component.
 */
class SequenciedSettingsWidget : public QWidget {
    Q_OBJECT

public:
    /**
     * @brief Constructs the SequenciedSettingsWidget.
     * @param parent Optional parent QWidget.
     */
    explicit SequenciedSettingsWidget(QWidget* parent = nullptr);

    /**
     * @brief Destructor.
     */
    ~SequenciedSettingsWidget();

    /**
     * @brief Refreshes the internal image list with image paths from a folder.
     * @param image_paths List of image file paths.
     */
    void flush_with_non_path(const QStringList& image_paths);

    /**
     * @brief Loads image list from a folder path.
     * @param list Folder path containing images.
     */
    void flush_images(const QString& list);

    /**
     * @brief Returns the current folder path from which images were loaded.
     * @return Path as a string.
     */
    QString folders_image_path() const;

    /**
     * @brief Returns the list of currently used image paths.
     * @return List of file paths.
     */
    QStringList get_image_lists() const;

    /**
     * @brief Gets the animation duration (ms).
     * @return Animation duration.
     */
    int getAnimation_duration() const;

    /**
     * @brief Sets the animation duration.
     * @param newAnimation_duration New duration in milliseconds.
     */
    void setAnimation_duration(int newAnimation_duration);

    /**
     * @brief Gets the wallpaper switching interval (ms).
     * @return Time interval.
     */
    int getWallpaper_switch_time() const;

    /**
     * @brief Sets the wallpaper switching interval.
     * @param newWallpaper_switch_time New interval in milliseconds.
     */
    void setWallpaper_switch_time(int newWallpaper_switch_time);

    /**
     * @brief get_easingcurve_type
     * @return
     */
    QEasingCurve get_easingcurve_type() const;

signals:
    /**
     * @brief Emitted when images should be loaded into a viewer.
     * @param imageLists List of image paths to load.
     */
    void loadToImageListView(const QStringList& imageLists);

    /**
     * @brief Emitted when image sources should be reinstalled.
     * @param imageLists New list of image sources.
     */
    void reinstalls(const QStringList& imageLists);

private slots:
    /**
     * @brief Handles user interaction with a specific image.
     * @param map Path to the clicked image.
     */
    void process_clicked_pixmaps(const QString& map);

    /**
     * @brief Applies changes and updates image list.
     */
    void apply_new_images();

private:
    Ui::SequenciedSettingsWidget* ui; ///< UI components pointer.
    ImageListViewer* viewer; ///< Reference to the image preview/viewer.
    QString image_lists_folders; ///< Folder path for loaded images.
    QStringList image_lists; ///< List of image paths.
    int animation_duration; ///< Duration of transition animations.
    int wallpaper_switch_time; ///< Interval for switching images.
    QEasingCurve curve; ///< curve types
    /**
     * @brief Enforces logical constraints on timing values.
     *
     * Ensures that switching interval is always longer than animation duration.
     */
    void enforceTimeConstraint();
};

#endif // SEQUENCIEDSETTINGSWIDGET_H
