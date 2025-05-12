#ifndef CCMEDIAPLAYLIST_H
#define CCMEDIAPLAYLIST_H

#include <QObject>

struct MediaListMails {
	bool prev_enabled { false }, next_enabled { false };
	QString current_playing {};
};

class CCMediaPlayList : public QObject {
	Q_OBJECT
public:
	explicit CCMediaPlayList(QObject* parent = nullptr);
	enum class PlayMode {
		OneShot, /* one shot makes the  */
		OneCycle, /* play current again and again ~ */
		ListPlay, /* play in the list, till the end we stop */
		ListCycle, /* cycling play the list */
	};

	static constexpr const PlayMode DEF_MODE = PlayMode::ListCycle;

	/* set the play mode */
	void set_play_mode(const PlayMode mode);
	void flow_mode();
	/* mode */
	inline PlayMode get_play_mode() const { return current_mode; }
	/* fetch the should play according modes and list */
	MediaListMails fetch_prev_play();
	/* fetch the next play */
	MediaListMails fetch_next_play();
	/* fetch current play */
	MediaListMails fetch_current_play() {
		return fetch_from_name(actual_play_list.at(moving_index));
	}
	/* fetch from given name */
	MediaListMails fetch_from_name(const QString& where);
	/* fetch the first play */
	MediaListMails fetch_first_play();
	/* fetch the last play */
	MediaListMails fetch_last_play();

	/* Playlist */
	QStringList currentPlayingList() const { return actual_play_list; }
	/* get the real playing list */
	QStringList actualList() const { return play_list; }
	/* get the actual play list size */
	int get_actualListlist_size() { return play_list.size(); }

	/* enqueue the play */
	void
	enqueue_play(const QStringList& media_sources);
	/* delete the playlist */
	void remove_play_list(const QStringList& media_sources);
signals:
	void playModeChanged(const PlayMode mode);

public slots:
	/*
	 * flush the play list, moves the playlist into actual one
	 */
	void flush_play_list();

private:
	PlayMode current_mode { DEF_MODE };
	/* we make changes here */
	QStringList play_list {};
	/*
	 * these is the actual playlist,
	 * when receiving the flush issue
	 */
	QStringList actual_play_list {};
	int moving_index { -1 };
	/* invoke flush once means the step forward */
	enum Direction {
		FORWARD,
		BACKWARD
	};

	void flush_info_according_mode(Direction dir);
	MediaListMails flush_according_index();
};

#endif // CCMEDIAPLAYLIST_H
