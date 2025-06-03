#include "Obsticals.h"
#include "figure/dinasour/Dinasour.h"
#include <QMutex>
#include <QRandomGenerator>
#include <QRect>
Obsticals::Obsticals(QObject* parent)
	: FigureObject { parent } {
}

bool Obsticals::is_intersect(Dinasour* dinasour) {
	return this->provide_current_bounding_rect().intersects(
		dinasour->provide_current_bounding_rect());
}

void Obsticals::set_moving_speed(const int speed) {
	QMutexLocker l(mutex.get());
	if (moving_speed != speed) {
		moving_speed = speed;
		emit speedChanged(moving_speed);
	}
}

void Obsticals::update_position() {
	auto& obs_rect = this->provide_current_bounding_rect();
	obs_rect.translate(-moving_speed, 0);

	if (obs_rect.right() >= 0) {
		return;
	}
	/* if we moves out to the
	 * left bound, that means the player pass
	 * obstacle, then, moves randomly to the right bound
	 * also emit a simple signal
	 */
	obs_rect.moveLeft(
		Settings::Scene::SCENE_FIXED_SZ.first);
	emit pass_me_already();
}
