#include "DifficultyManager.h"
#include "settings/setting_scene.h"
#include <QTimer>
DifficultyManager::DifficultyManager(QObject* parent)
	: QObject { parent } {
	using namespace Settings::Scene::Difficulty;
	this->current_difficulty = START_DIFFICULTY;
	auto_update_timer = new QTimer(this);
	auto_update_timer->setInterval(INIT_PEROID);
	connect(this, &DifficultyManager::difficulty_changed,
			this, &DifficultyManager::process_difficulty_changed);
	connect(auto_update_timer, &QTimer::timeout, this,
			&DifficultyManager::upgrade_difficulty);
}

void DifficultyManager::upgrade_difficulty() {
	if (current_difficulty >= MAX_DIFFICULTY) {
		return;
	}
	int index = static_cast<int>(current_difficulty);
	index++;
	current_difficulty = static_cast<Difficulty>(index);
	emit difficulty_changed(current_difficulty);
}

void DifficultyManager::set_auto_update(bool st) {
	if (current_difficulty == Difficulty::HOLY_SHIT) {
		auto_update_timer->stop();
		return;
	}
	st ? auto_update_timer->start() : auto_update_timer->stop();
}

void DifficultyManager::force_reset() {
	this->current_difficulty = Settings::Scene::Difficulty::START_DIFFICULTY;
}

void DifficultyManager::process_difficulty_changed() {
	using namespace Settings::Scene::Difficulty;
	switch (current_difficulty) {
	case Difficulty::EASY:
		emit new_move_speed(SPEED_EASY);
		emit new_obstacle_cnt_max(MAX_OBS_CNT - 3);
		auto_update_timer->setInterval(SIMPLE_PEROID);
		break;
	case Difficulty::MEDIUM:
		emit new_move_speed(SPEED_MEDIUM);
		emit new_obstacle_cnt_max(MAX_OBS_CNT - 2);
		auto_update_timer->setInterval(MEDIUM_PEROID);
		break;
	case Difficulty::HARD:
		emit new_move_speed(SPEED_HARD);
		emit new_obstacle_cnt_max(MAX_OBS_CNT - 1);
		auto_update_timer->setInterval(HARD_PEROID);
		break;
	case Difficulty::HOLY_SHIT:
		/* holy max! */
		emit new_move_speed(SPEED_MAX);
		emit new_obstacle_cnt_max(MAX_OBS_CNT);
		auto_update_timer->stop();
		break;
	}
}
