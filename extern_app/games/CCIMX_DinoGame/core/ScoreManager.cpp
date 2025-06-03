#include "ScoreManager.h"
#include "settings/settings_score.h"
#include <QMutex>
#include <QTimer>

void ScoreManager::set_score_increase_step(int step) {
	QMutexLocker l(mutex_locker.get());
	this->step = step;
}

ScoreManager::ScoreManager(QObject* parent)
	: QObject(parent) {
	auto_update_timer = new QTimer(this);
	auto_update_timer->setInterval(Settings::Score::TIME_PERIOD_AUTO_ADD);
	connect(auto_update_timer, &QTimer::timeout,
			this, static_cast<void (ScoreManager::*)()>(&ScoreManager::increase_once));
}

void ScoreManager::increase_once() {
	QMutexLocker l(mutex_locker.get());
	score += step;
}

void ScoreManager::increase_once(int score) {
	QMutexLocker l(mutex_locker.get());
	this->score += score;
}

void ScoreManager::set_increase_automatically(bool st) {
	st ? auto_update_timer->start() : auto_update_timer->stop();
}

void ScoreManager::force_reset() {
	auto_update_timer->stop();
	this->score = 0;
}
