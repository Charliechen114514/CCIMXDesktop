#include "Dinasour.h"
#include "settings/setting_scene.h"
#include "settings/settings_figure.h"
#include "ui/FigureFrameFetcher.h"

Dinasour::Dinasour(QObject* parent)
	: FigureObject { parent } {
	setup_frame_provider();
}

void Dinasour::make_jump() {
	jump_rect = provide_current_bounding_rect();
	is_jumping = true;
	using namespace Settings::Figure::Dinasour;
	velocityY = JUMP_ABILITY;
}

void Dinasour::set_laying(bool st) {
	is_laying = st;
	if (st) {
		set_providing_state(State::LAYING);
	} else {
		set_providing_state(State::RUNNING);
	}
}

void Dinasour::process_animation() {
	using namespace Settings::Scene;

	QRect& rect = is_jumping ? jump_rect : provide_current_bounding_rect();

	rect.translate(0, velocityY);
	velocityY += Grivity::Y_G_APPEND;
	if (is_laying) {
		velocityY += Grivity::Y_G_APPEND;
	}

	if (rect.bottom() >= Ground::GROUND_Y_POS) {
		rect.moveBottom(Ground::GROUND_Y_POS);
		velocityY = 0;

		if (is_jumping) {
			is_jumping = false;
			provide_current_bounding_rect() = jump_rect;
		}
	}
}

void Dinasour::set_providing_state(State s) {
	current_state = s;
	switch (current_state) {
	case State::READY:
	case State::DIE:
		normal_run->terminate_flow();
		lay_run->terminate_flow();
		break;
	case State::RUNNING:
		normal_run->resume_flow();
		lay_run->terminate_flow();
		break;
	case State::LAYING:
		lay_run->resume_flow();
		normal_run->terminate_flow();
		break;
	}
}

QRect& Dinasour::provide_current_bounding_rect() {
	if (is_jumping) {
		return jump_rect;
	}

	switch (current_state) {
	case State::READY:
	case State::RUNNING:
	case State::DIE:
		return normal_run->src_bounding_rect();
	case State::LAYING:
		return lay_run->src_bounding_rect();
	}
	return normal_run->src_bounding_rect();
}

QPixmap& Dinasour::provide_drawing_srcframe() {
	switch (current_state) {
	case State::READY:
		return ready_map;
	case State::RUNNING:
		return normal_run->src_pixmap();
	case State::LAYING:
		return lay_run->src_pixmap();
	case State::DIE:
		return die_map;
	}
	return die_map;
}

void Dinasour::setup_frame_provider() {
	using namespace Settings;
	using namespace Settings::Scene;

	ready_map.load(Figure::Dinasour::FRAME_1);
	die_map.load(Figure::Dinasour::FRAME_SHIT);

	normal_run = new DinasourFrameFetcher(Figure::Dinasour::FRAME_1, this);
	normal_run->terminate_flow();
	normal_run->append_src(Figure::Dinasour::FRAME_2);
	normal_run->set_frame_state(DinasourFrameFetcher::State::NORMAL);

	lay_run = new DinasourFrameFetcher(Figure::Dinasour::FRAME_1, this);
	lay_run->terminate_flow();
	lay_run->append_src(Figure::Dinasour::FRAME_2);
	lay_run->set_frame_state(DinasourFrameFetcher::State::LAY);
}
