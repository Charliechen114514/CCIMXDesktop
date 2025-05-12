#include "CCMediaPlayList.h"

CCMediaPlayList::CCMediaPlayList(QObject* parent)
	: QObject { parent } {
}

void CCMediaPlayList::set_play_mode(const PlayMode mode) {
	current_mode = mode;
	emit playModeChanged(mode);
}

void CCMediaPlayList::flow_mode() {
	switch (current_mode) {
	case PlayMode::OneShot:
		current_mode = PlayMode::OneCycle;
		break;
	case PlayMode::OneCycle:
		current_mode = PlayMode::ListPlay;
		break;
	case PlayMode::ListPlay:
		current_mode = PlayMode::ListCycle;
		break;
	case PlayMode::ListCycle:
		current_mode = PlayMode::OneShot;
		break;
	}
	emit playModeChanged(current_mode);
}

MediaListMails CCMediaPlayList::fetch_prev_play() {
	MediaListMails mails;
	if (actual_play_list.isEmpty()) {
		mails.prev_enabled = false;
		mails.next_enabled = false;
		return mails;
	}
	moving_index--;
	flush_info_according_mode(Direction::BACKWARD);
	return flush_according_index();
}

MediaListMails CCMediaPlayList::fetch_next_play() {
	MediaListMails mails;
	if (actual_play_list.isEmpty()) {
		mails.prev_enabled = false;
		mails.next_enabled = false;
		return mails;
	}
	moving_index++;
	flush_info_according_mode(Direction::FORWARD);
	return flush_according_index();
}

MediaListMails CCMediaPlayList::fetch_from_name(const QString& where) {
	MediaListMails mails;
	if (actual_play_list.isEmpty()) {
		mails.prev_enabled = false;
		mails.next_enabled = false;
		return mails;
	}

	int possible_index = actual_play_list.indexOf(where);
	if (possible_index == -1) {
		mails.prev_enabled = false;
		mails.next_enabled = false;
		return mails;
	}

	moving_index = possible_index;
	return flush_according_index();
}

MediaListMails CCMediaPlayList::fetch_first_play() {
	MediaListMails mails;
	if (actual_play_list.isEmpty()) {
		mails.prev_enabled = false;
		mails.next_enabled = false;
		return mails;
	}
	moving_index = 0;
	return flush_according_index();
}

MediaListMails CCMediaPlayList::fetch_last_play() {
	MediaListMails mails;
	if (actual_play_list.isEmpty()) {
		mails.prev_enabled = false;
		mails.next_enabled = false;
		return mails;
	}
	moving_index = actual_play_list.size() - 1;
	return flush_according_index();
}

void CCMediaPlayList::enqueue_play(const QStringList& media_sources) {
	play_list.append(media_sources);
	actual_play_list = play_list;
	moving_index = 0;
}

void CCMediaPlayList::remove_play_list(const QStringList& media_sources) {
	for (const auto& source : media_sources) {
		play_list.removeAll(source);
	}
}

/* make flush, and written the issue */
void CCMediaPlayList::flush_play_list() {
	actual_play_list = play_list;
}

void CCMediaPlayList::flush_info_according_mode(Direction dir) {
	switch (current_mode) {
	case PlayMode::OneShot: {
		/* nothing change */
	} break;
	case PlayMode::OneCycle: {
		switch (dir) {
		case FORWARD:
			moving_index--;
			break;
		case BACKWARD:
			moving_index++;
			break;
		}
	} break;
	case PlayMode::ListPlay: {
		/* also do nothing */
	}
	case PlayMode::ListCycle:
		if (moving_index >= actual_play_list.size()) {
			moving_index = 0;
		} else if (moving_index < 0) {
			moving_index = actual_play_list.size() - 1;
		}
		break;
	}
}

MediaListMails CCMediaPlayList::flush_according_index() {
	MediaListMails mails;
	/* recyclable makes no edge */
	if (current_mode == PlayMode::OneCycle || current_mode == PlayMode::ListCycle) {
		mails.next_enabled = moving_index <= actual_play_list.size() - 1;
		mails.prev_enabled = moving_index >= 0;
	} else {
		mails.next_enabled = moving_index < actual_play_list.size() - 1;
		mails.prev_enabled = moving_index > 0;
	}

	mails.current_playing = actual_play_list[moving_index];
	return mails;
}
