#include "ObstacleListManager.h"
#include "figure/obstacle/BirdObsticals.h"
#include "figure/obstacle/CactusObsticals.h"
#include "settings/setting_scene.h"
#include "settings/settings_figure.h"
#include <QMutex>
#include <QRandomGenerator>
#include <QRect>
#include <QSet>
#include <QTimer>
namespace {
QList<Obsticals*> filterObstacles(QList<Obsticals*>& result,
                                  QList<Obsticals*>& src,
                                  int count) {
    QSet<Obsticals*> srcSet(src.begin(), src.end());

	QList<Obsticals*> filtered;
	filtered.reserve(count);

	for (Obsticals* obs : result) {
		if (!srcSet.contains(obs)) {
			filtered.append(obs);
			if (filtered.size() >= count)
				break;
		}
	}

	return filtered;
}

}

ObstacleListManager::ObstacleListManager(QObject* parent)
	: QObject { parent } {
	using namespace Settings::Scene::Difficulty;
	obs_max_count = INIT_OBS_CNT;
	locker = std::make_shared<QMutex>();
	init_instance_pool();
}

QList<Obsticals*> ObstacleListManager::get_should_render() {
	return activate_obsticals;
}

void ObstacleListManager::start_blank_working() {
	using namespace Settings::Figure::Bird;
	QTimer::singleShot(BIRD_APPEAR_AT_MSEC, this, &ObstacleListManager::let_bird_appear);
}

void ObstacleListManager::animate_once() {
	flush_activate_obsticals_once();
	for (auto& activate : activate_obsticals) {
		activate->update_position();
	}
}

void ObstacleListManager::reset_back() {
	activate_obsticals.clear();
	should_bird_appear = false;
}

bool ObstacleListManager::is_intersects(Dinasour* dinasour) {
	for (auto& activate : activate_obsticals) {
		if (activate->is_intersect(dinasour)) {
			return true;
		}
	}
	return false;
}

QList<Obsticals*> ObstacleListManager::get_pools() {
	QList<Obsticals*> all;
	for (const auto each : std::as_const(activate_obsticals)) {
		all << each;
	}
	return all;
}

void ObstacleListManager::set_max_obstacle_cnt(short max_count) {
	using namespace Settings::Scene::Difficulty;
	if (max_count > MAX_OBS_CNT) {
		return;
	}
	obs_max_count = max_count;
}

int ObstacleListManager::get_obstacle_speed() {
	if (!cactus_obsticals_pool.empty()) {
		return cactus_obsticals_pool[0]->get_moving_speed();
	}
	return 0;
}

void ObstacleListManager::process_random_summon_once() {
	short push_num = QRandomGenerator::global()->bounded(obs_max_count);
	if (push_num == 0) {
		push_num = 1;
	} else if (push_num < obs_max_count / 2) {
		push_num = obs_max_count - 1;
	}

	/* process the cactus */
	auto new_members = query_unactivates(BaseType::Cactus, push_num);
	int start_x = get_max_right_x_of_actives();
	start_x = adjustif_new_members(new_members, start_x);
	activate_obsticals.append(new_members);

	/* process the bird */
	if (should_bird_appear) {
		push_num = obs_max_count - push_num;
		new_members.clear();
		new_members = query_unactivates(BaseType::Bird, push_num);
		adjustif_new_members(new_members, start_x); // 注意这里用了刚才调整后的 start_x
		activate_obsticals.append(new_members);
	}
}

int ObstacleListManager::get_max_right_x_of_actives() const {
	int max_x = 0;
	for (auto* obs : activate_obsticals) {
		max_x = std::max(max_x, obs->provide_current_bounding_rect().right());
	}
	if (max_x == 0) {
		max_x = Settings::Scene::SCENE_FIXED_SZ.first;
	}
	return max_x;
}

int ObstacleListManager::adjustif_new_members(const QList<Obsticals*>& new_members, int start_x) {
	if (new_members.empty()) {
		return start_x;
	}
	int x = start_x;
	using namespace Settings::Figure::Obstacle;
	for (auto* obs : new_members) {
		QRect& rect = obs->provide_current_bounding_rect();
		rect.moveLeft(x);
		int gap = QRandomGenerator::global()->bounded(
			MOVE_BOUND_OUT, MOVE_BOUND_OUT + MOVE_BOUND_GAP);
		x = rect.right() + gap;
	}
	return x;
}

void ObstacleListManager::flush_activate_obsticals_once() {
	QMutexLocker<QMutex> l(locker.get());
	if (activate_obsticals.empty()) {
		process_random_summon_once();
	}
}

#include <QPropertyAnimation>
void ObstacleListManager::set_obstacle_speed(int speed) {
	QMutexLocker<QMutex> l(locker.get());
	for (auto& obstacle : std::as_const(this->cactus_obsticals_pool)) {
		// each->set_moving_speed(speed);
		QPropertyAnimation* animation = new QPropertyAnimation(obstacle, "moving_speed");
		animation->setDuration(1000);
		animation->setStartValue(obstacle->get_moving_speed());
		animation->setEndValue(speed);
		animation->setEasingCurve(QEasingCurve::InOutQuad);
		animation->start(QAbstractAnimation::DeleteWhenStopped);
	}

	for (auto& obstacle : std::as_const(this->brid_obsticals_pool)) {
		// each->set_moving_speed(speed);
		QPropertyAnimation* animation = new QPropertyAnimation(obstacle, "moving_speed");
		animation->setDuration(1000);
		animation->setStartValue(obstacle->get_moving_speed());
		animation->setEndValue(speed);
		animation->setEasingCurve(QEasingCurve::InOutQuad);
		animation->start(QAbstractAnimation::DeleteWhenStopped);
	}
}

QList<Obsticals*> ObstacleListManager::query_unactivates(BaseType t, int how_many) {
	QList<Obsticals*> result;

	switch (t) {
	case BaseType::Cactus: {
		QList<Obsticals*> baseList;
		for (CactusObsticals*& cactus : this->cactus_obsticals_pool) {
			baseList.append(static_cast<Obsticals*>(cactus));
		}
		result = filterObstacles(baseList, this->activate_obsticals, how_many);
	} break;

	case BaseType::Bird: {
		QList<Obsticals*> baseList;
		for (BirdObsticals*& brid : this->brid_obsticals_pool) {
			baseList.append(static_cast<Obsticals*>(brid));
		}
		result = filterObstacles(baseList, this->activate_obsticals, how_many);
	} break;
	}

	return result;
}

void ObstacleListManager::init_instance_pool() {
	using namespace Settings::Scene::Difficulty;
	/* cactus */
	cactus_obsticals_pool.resize(MAX_OBS_CNT);
	for (int i = 0; i < MAX_OBS_CNT; i++) {
		auto instance = new CactusObsticals(this);
		instance->setAutoUpdateSzRandomly(true);
		cactus_obsticals_pool[i] = instance;
		connect(instance, &CactusObsticals::pass_me_already,
				this, &ObstacleListManager::process_internal_pass_session);
	}

	/* bird */
	brid_obsticals_pool.resize(MAX_OBS_CNT);
	for (int i = 0; i < MAX_OBS_CNT; i++) {
		auto instance = new BirdObsticals(this);
		brid_obsticals_pool[i] = instance;
		connect(instance, &BirdObsticals::pass_me_already,
				this, &ObstacleListManager::process_internal_pass_session);
	}
}

void ObstacleListManager::process_internal_pass_session() {
	Obsticals* obs = dynamic_cast<Obsticals*>(sender());
	if (!obs) {
		qDebug() << "What the Fuck? not a Obsticals???";
		return;
	}

	if (!activate_obsticals.contains(obs)) {
		qDebug() << "What the Fuck? not in activate???";
		return;
	} else {
		activate_obsticals.removeAll(obs);
	}

	/* check the details */
	ObstacleType type = ObstacleType::UNKNOWN;
	CactusObsticals* possible_cac = dynamic_cast<CactusObsticals*>(obs);
	if (possible_cac) {
		/* is a cactus */
		switch (possible_cac->getSize()) {
		case CactusObsticals::Size::SMALL:
			type = ObstacleType::SmallCactus;
			break;
		case CactusObsticals::Size::MEDIUM:
			type = ObstacleType::MedCactus;
			break;
		case CactusObsticals::Size::LARGE:
			type = ObstacleType::LargeCactus;
			break;
		}
	} else {
		BirdObsticals* bird = dynamic_cast<BirdObsticals*>(obs);
		if (bird) {
			switch (bird->getSize()) {
			case BirdObsticals::BirdType::SMALL:
				type = ObstacleType::SmallBird;
				break;
			case BirdObsticals::BirdType::MEDIUM:
				type = ObstacleType::MediumBird;
				break;
			case BirdObsticals::BirdType::LARGE:
				type = ObstacleType::LargeBird;
				break;
			}
		}
	}

	// emit the signals for decisions
	emit pass_a_obstacle(type, obs);
}
