#ifndef CCMEDIAPLAYLIST_H
#define CCMEDIAPLAYLIST_H

#include <QObject>

/**
 * @brief The MediaListMails class provides the medias play info
 * @note this is the mail list for the media current play
 */
struct MediaListMails {
	bool prev_enabled { false }, next_enabled { false };
	QString current_playing {};
};

class CCMediaPlayList : public QObject {
	Q_OBJECT
public:
	explicit CCMediaPlayList(QObject* parent = nullptr);

	/**
	 * @brief The PlayMode enum provides the play modes
	 */
	enum class PlayMode {
		OneShot, ///< play one time, then stop
		OneCycle, ///< play current again and again ~
		ListPlay, ///< play the list once
		ListCycle, ///< play the list again and again ~
	};

	/**
	 * @brief DEF_MODE the default play mode
	 */
	static constexpr const PlayMode DEF_MODE = PlayMode::ListCycle;

	/**
	 * @brief set_play_mode set the play mode
	 * @param mode the play mode to set
	 */
	void set_play_mode(const PlayMode mode);

	/**
	 * @brief flow_mode flow the mode once
	 */
	void flow_mode();

	/**
	 * @brief get_play_mode get the play mode
	 * @return the play mode
	 */
	inline PlayMode get_play_mode() const { return current_mode; }

	/**
	 * @brief fetch_prev_play fetch the previous play
	 * @return the previous play
	 */
	MediaListMails fetch_prev_play();

	/**
	 * @brief fetch_next_play fetch the next play
	 * @return the next play
	 */
	MediaListMails fetch_next_play();

	/**
	 * @brief fetch_current_play fetch the current play
	 * @return the current play
	 */
	MediaListMails fetch_current_play() {
		return fetch_from_name(actual_play_list.at(moving_index));
	}

	/**
	 * @brief fetch_from_name fetch the play from name
	 * @param where the name to fetch
	 * @return the play info
	 */
	MediaListMails fetch_from_name(const QString& where);

	/**
	 * @brief fetch_first_play fetch the first play
	 * @return the first play
	 */
	MediaListMails fetch_first_play();

	/**
	 * @brief fetch_last_play fetch the last play
	 * @return the last play
	 */
	MediaListMails fetch_last_play();

	/**
	 * @brief currentPlayingList get the actual play list
	 * @return the actual play list
	 * @note diffrently, this means the list really playings, that means
	 * any modifications wont do the stuff here, what we get the list
	 * we really play and operate
	 */
	QStringList currentPlayingList() const { return actual_play_list; }

	/**
	 * @brief actualList get the current playing list
	 * @return the current playing list
	 * @note this means the list that holding really, for examples
	 * when we modified the list and ready check the situations, use this
	 */
	QStringList actualList() const { return play_list; }

	/**
	 * @brief get_actualListlist_size get the actual list size
	 * @return the actual list size
	 * @note this is the size of the play list, not the actual one
	 */
	int get_actualListlist_size() { return play_list.size(); }

	/**
	 * @brief enqueue_play enqueue the play list
	 * @param media_sources the media sources to enqueue
	 */
	void
	enqueue_play(const QStringList& media_sources);

	/**
	 * @brief remove_play_list remove the play list
	 * @param media_sources the media sources to remove
	 */
	void remove_play_list(const QStringList& media_sources);
signals:
	/**
	 * @brief playModeChanged the signal indicating the play mode changed
	 * @param mode the play mode
	 */
	void playModeChanged(const PlayMode mode);

public slots:
	/**
	 * @brief flush_play_list flush the play list,
	 * moves the playlist into actual one
	 */
	void flush_play_list();

private:
	PlayMode current_mode { DEF_MODE }; ///< the current play mode
	QStringList play_list {}; ///< we make changes here

	QStringList actual_play_list {}; ///< the actual play list, when receiving the flush issue
	int moving_index { -1 }; ///< the moving index, where are we in the lists

	enum Direction {
		FORWARD, ///< forward, moves to the next
		BACKWARD ///< backward, moves to the previous
	};

	/**
	 * @brief flush_info_according_mode flush the play list according the mode
	 * @param dir the direction to flush
	 */
	void flush_info_according_mode(Direction dir);

	/**
	 * @brief flush_according_index flush the play list according the index
	 * @return the play list mails
	 */
	MediaListMails flush_according_index();
};

#endif // CCMEDIAPLAYLIST_H
