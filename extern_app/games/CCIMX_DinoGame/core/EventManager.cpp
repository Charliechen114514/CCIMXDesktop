#include "EventManager.h"
#include "DinasourGameMainWidget.h"
#include "figure/dinasour/Dinasour.h"
#include <QKeyEvent>
#include <QMouseEvent>
void EventManager::install_keyPress_keyEvent(QKeyEvent* keyEvent) {
	this->ind = Indication::NOTHING;
	if (keyEvent->key() == Qt::Key_Space) {
		if (holdings->is_game_over()) {
			return;
		}

		if (holdings->get_dinasour_instance()->isJumping()) {
			return;
		}

		this->ind = holdings->is_game_started() ? Indication::JUMP : Indication::LAUNCH_GAME;
		return;
	}

	if (keyEvent->key() == Qt::Key_Down) {
		if (holdings->is_game_over()) {
			return;
		}

		if (holdings->get_dinasour_instance()->isLaying()) {
			return;
		}
		this->ind = Indication::LAY;
	}
}

void EventManager::install_keyRelease_keyEvent(QKeyEvent* keyEvent) {
	release_ind = KeyReleaseIndication::NOTHING;
	if (keyEvent->key() == Qt::Key_Down) {
		release_ind = KeyReleaseIndication::RELAX;
	}
}

void EventManager::install_mousepress_event(QMouseEvent* mouseEvent) {
	this->ind = Indication::NOTHING;
	if (holdings->is_game_over()) {
		return;
	}

	if (holdings->get_dinasour_instance()->isJumping()) {
		return;
	}

	this->ind = holdings->is_game_started() ? Indication::JUMP : Indication::LAUNCH_GAME;
	return;
}
