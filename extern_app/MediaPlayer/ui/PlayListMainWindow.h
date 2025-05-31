#ifndef PLAYLISTMAINWINDOW_H
#define PLAYLISTMAINWINDOW_H

#include <QMainWindow>

// Forward declaration of UI class
namespace Ui {
class PlayListMainWindow;
}

/**
 * @class PlayListMainWindow
 * @brief Main window for playlist management functionality
 *
 * Provides interface for viewing and managing media playlists,
 * including playing, deleting, and editing playlist items.
 */
class PlayListMainWindow : public QMainWindow {
    Q_OBJECT

public:
    /**
     * @brief Constructor
     * @param parent Parent widget
     */
    explicit PlayListMainWindow(QWidget* parent = nullptr);

    /**
     * @brief Toggle between edit and view modes
     * 
     * Switches the playlist between editable and non-editable states,
     * typically showing/hiding delete buttons and enabling/disabling
     * item rearrangement.
     */
    void flip_edit_mode();

    /**
     * @brief Destructor
     */
    ~PlayListMainWindow();

signals:
    /**
     * @brief Signal to request refreshing the media list
     * @note Emitted when playlist items are pressed or modified
     */
    void refresh_media_list();

    /**
     * @brief Signal to request playing a specific media item
     * @param media_src Path or identifier of the media to play
     */
    void play_media(const QString& media_src);

    /**
     * @brief Signal to request deleting a media item from playlist
     * @param media_src Path or identifier of the media to delete
     */
    void delete_media(const QString& media_src);

public slots:
    /**
     * @brief Populate the playlist from a string list
     * @param l List of media sources (paths/URLs) to populate
     */
    void from_media_list(const QStringList& l);

private slots:
    /**
     * @brief Handle delete action for selected items
     * 
     * Processes the deletion of currently selected playlist items,
     * typically triggered from a delete button in edit mode.
     */
    void process_select_delete();

    /**
     * @brief Handle item click events
     * 
     * Processes user clicks on playlist items, typically triggering
     * playback of the selected item.
     */
    void process_item_click();

private:
    Ui::PlayListMainWindow* ui;  ///< Pointer to UI components
    bool in_edit_mode { false }; ///< Current mode flag (true = edit mode)
};

#endif // PLAYLISTMAINWINDOW_H