#ifndef CCMEDIAPLAYLIST_H
#define CCMEDIAPLAYLIST_H

#include <QObject>

/**
 * @brief The MediaListMails struct provides play status info
 * @note Contains flags for prev/next availability and current playing name
 */
struct MediaListMails {
    bool prev_enabled { false }; ///< Whether previous item can be played
    bool next_enabled { false }; ///< Whether next item can be played
    QString current_playing {};  ///< The current playing media name or path
};

/**
 * @brief The CCMediaPlayList class manages a playlist with various play modes.
 */
class CCMediaPlayList : public QObject {
    Q_OBJECT
public:
	/**
 	* @brief Construct a new CCMediaPlayList object
 	* 
 	* @param parent 
 	*/
    explicit CCMediaPlayList(QObject* parent = nullptr);

    /**
     * @brief PlayMode enum defines playback modes
     */
    enum class PlayMode {
        OneShot,    ///< Play one media once then stop
        OneCycle,   ///< Repeat the current media endlessly
        ListPlay,   ///< Play the playlist once in order
        ListCycle   ///< Play the playlist repeatedly
    };

    static constexpr const PlayMode DEF_MODE = PlayMode::ListCycle; ///< Default play mode

    /**
     * @brief Set the play mode
     * @param mode PlayMode to set
     */
    void set_play_mode(const PlayMode mode);

    /**
     * @brief Cycle the play mode to the next one
     */
    void flow_mode();

    /**
     * @brief Get current play mode
     * @return current PlayMode
     */
    inline PlayMode get_play_mode() const { return current_mode; }

    /**
     * @brief Fetch previous media info according to play mode
     * @return MediaListMails containing prev enabled flag and current playing info
     */
    MediaListMails fetch_prev_play();

    /**
     * @brief Fetch next media info according to play mode
     * @return MediaListMails containing next enabled flag and current playing info
     */
    MediaListMails fetch_next_play();

    /**
     * @brief Fetch current media info
     * @return MediaListMails of currently playing media
     */
    MediaListMails fetch_current_play() {
        return fetch_from_name(actual_play_list.at(moving_index));
    }

    /**
     * @brief Fetch media info by name
     * @param where The media name or path to fetch
     * @return MediaListMails with play info for the given media
     */
    MediaListMails fetch_from_name(const QString& where);

    /**
     * @brief Fetch first media info in the actual playlist
     * @return MediaListMails of first media
     */
    MediaListMails fetch_first_play();

    /**
     * @brief Fetch last media info in the actual playlist
     * @return MediaListMails of last media
     */
    MediaListMails fetch_last_play();

    /**
     * @brief Get the current actual playing list
     * @return QStringList of media actually played
     * @note This list is the one actively used for playback (immutable until flushed)
     */
    QStringList currentPlayingList() const { return actual_play_list; }

    /**
     * @brief Get the editable play list
     * @return QStringList of media in play list (modifiable)
     */
    QStringList actualList() const { return play_list; }

    /**
     * @brief Get size of the editable play list
     * @return int size of play_list
     */
    int get_actualListlist_size() { return play_list.size(); }

    /**
     * @brief Append media sources to the play list
     * @param media_sources List of media paths/names to add
     */
    void enqueue_play(const QStringList& media_sources);

    /**
     * @brief Remove media sources from the play list
     * @param media_sources List of media paths/names to remove
     */
    void remove_play_list(const QStringList& media_sources);

signals:
    /**
     * @brief Signal emitted when play mode changes
     * @param mode The new PlayMode
     */
    void playModeChanged(const PlayMode mode);

public slots:
    /**
     * @brief Flush the editable play list into actual_play_list, making changes effective
     */
    void flush_play_list();

private:
    PlayMode current_mode { DEF_MODE }; ///< Current play mode
    QStringList play_list {}; ///< Editable play list (modifiable)
    QStringList actual_play_list {}; ///< Active play list (effective for playback)
    int moving_index { -1 }; ///< Current position index in actual_play_list

    enum Direction {
        FORWARD,  ///< Move forward in playlist
        BACKWARD  ///< Move backward in playlist
    };

    /**
     * @brief Update moving_index and play info based on direction and play mode
     * @param dir Direction to move
     */
    void flush_info_according_mode(Direction dir);

    /**
     * @brief Generate MediaListMails based on current moving_index
     * @return MediaListMails describing current play state
     */
    MediaListMails flush_according_index();
};

#endif // CCMEDIAPLAYLIST_H
