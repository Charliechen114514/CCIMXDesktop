#ifndef MEDIAPLAYERWINDOW_H
#define MEDIAPLAYERWINDOW_H

#include "core/CCMediaPlayList.h"
#include <QMainWindow>

// Forward declarations
class MediaPlayer;
class MediaInfoWindow;
class PlayListMainWindow;

QT_BEGIN_NAMESPACE
namespace Ui {
class MediaPlayerWindow;
}
QT_END_NAMESPACE

/**
 * @class MediaPlayerWindow
 * @brief Main window class for media player application
 *
 * Provides the main interface for media playback including controls,
 * playlist management, and media information display.
 */
class MediaPlayerWindow : public QMainWindow {
    Q_OBJECT

public:
    friend class MediaPlayerWindowHelper;  ///< Grant access to helper class
    
    /**
     * @brief Constructor
     * @param parent Parent widget
     */
    explicit MediaPlayerWindow(QWidget* parent = nullptr);
    
    /* Media control functions */
    
    /**
     * @brief Open single media file via file dialog
     */
    void open_media();
    
    /**
     * @brief Open multiple media files via file dialog
     */
    void open_medias();
    
    /**
     * @brief Toggle between play/pause states
     */
    void toggle_playing_status();
    
    /**
     * @brief Skip forward 10 seconds in current media
     */
    void forward10sec();
    
    /**
     * @brief Skip backward 10 seconds in current media
     */
    void backward10sec();
    
    /**
     * @brief Set flow mode to play current item once
     */
    void flow_mode_once();
    
    /**
     * @brief Destructor
     */
    ~MediaPlayerWindow();

private slots:
    /* Image handling slots */
    /**
     * @brief Handle availability of display image
     * @param available Whether image is available
     * @param image The image to display (if available)
     */
    void handle_display_src(bool available, const QImage& image);
    
    /**
     * @brief Handle new image for display
     * @param image The image to display
     */
    void handle_imageDisplay(const QImage& image);

    /* Progress and duration handling slots */
    /**
     * @brief Handle new media duration
     * @param duration Duration in milliseconds
     */
    void handle_new_durations(qint64 duration);
    
    /**
     * @brief Handle media position change
     * @param position Current position in milliseconds
     */
    void handle_position_changed(qint64 position);
    
    /**
     * @brief Handle media playback completion
     */
    void handle_media_end();

    /* Slider control slots */
    /**
     * @brief Handle slider position change
     * @param position New slider position
     */
    void handle_slider_position_changed(int position);
    
    /**
     * @brief Handle slider pressed event
     */
    void handle_slider_pressed();
    
    /**
     * @brief Handle slider released event
     */
    void handle_slider_released();

private:
    Ui::MediaPlayerWindow* ui;            ///< UI components
    MediaPlayer* mediaPlayer { nullptr }; ///< Core media player
    MediaInfoWindow* infoWindow { nullptr }; ///< Media info display
    CCMediaPlayList* medialist { nullptr }; ///< Playlist management
    PlayListMainWindow* playListWindow { nullptr }; ///< Playlist UI

    /* State flags */
    bool manual_sliding { false };  ///< Whether user is manually sliding
    bool is_playing { false };      ///< Current play/pause state
    bool video_available { false }; ///< Whether video stream is available

    /* Initialization methods */
    void init_memories();          ///< Initialize member objects
    void init_core_connections();  ///< Set up core signal-slot connections
    void init_ui_connections();    ///< Set up UI signal-slot connections
    void init_connections();       ///< Combined initialization of connections

    /* Media processing methods */
    /**
     * @brief Handle case when video stream is unavailable (audio only)
     */
    void post_do_video_unavailable();
    
    /**
     * @brief Perform post-UI initialization
     */
    void post_init_ui();
    
    /**
     * @brief Update UI for current play/pause state
     */
    void process_playing_status();
    
    /**
     * @brief Handle play mode switching
     */
    void process_playmode_switching();
    
    /**
     * @brief Handle media list notifications
     * @param mails Notification messages from media list
     */
    void handle_according_mails(const MediaListMails mails);
};

#endif // MEDIAPLAYERWINDOW_H