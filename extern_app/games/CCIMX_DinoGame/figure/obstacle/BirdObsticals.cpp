#include "BirdObsticals.h"
#include "FigureFrameFetcher.h"
#include "settings/settings_figure.h"
#include <QMutex>
#include <QRandomGenerator>
#include <QRect>
BirdObsticals::BirdObsticals(QObject* parent)
	: Obsticals { parent } {
	init_memory();
	// everytime we pass, we shell switch a new(oh, possiblly)
	// a new faces!
	connect(this, &BirdObsticals::pass_me_already,
			this, &BirdObsticals::update_frame);
}

void BirdObsticals::setHeight(FlyHeight h) {
	using namespace Settings::Figure::Bird;
	auto& rect = provide_current_bounding_rect();
	int bottom = 0;
	auto hei = rect.height();
	switch (h) {
	case FlyHeight::LOW:
		bottom = LOW_HEIGHT;
		break;
	case FlyHeight::MED:
		bottom = MED_HEIGHT;
		break;
	case FlyHeight::HIG:
		bottom = HIG_HEIGHT;
		break;
	}
	rect.setBottom(bottom);
	rect.setTop(bottom - hei + 1);
}

void BirdObsticals::setSize(BirdType t) {
	QMutexLocker l(mutex.get());
	type = t;
	using namespace Settings::Figure::Bird;
	QSize new_size;
	switch (type) {
	case BirdType::SMALL:
		new_size = { SmallBirdSize.first, SmallBirdSize.second };
		break;
	case BirdType::MEDIUM:
		new_size = { MediumBirdSize.first, MediumBirdSize.second };
		break;
	case BirdType::LARGE:
		new_size = { LargeBirdSize.first, LargeBirdSize.second };
		break;
	}

	auto& rect = provide_current_bounding_rect();
	rect.setSize(new_size);
	rect.setTop(rect.bottom() - new_size.height() + 1);
}

QRect& BirdObsticals::provide_current_bounding_rect() {
	return bird_frame_provider->src_bounding_rect();
}

QPixmap& BirdObsticals::provide_drawing_srcframe() {
	return bird_frame_provider->src_pixmap();
}

void BirdObsticals::init_memory() {
	using namespace Settings::Figure::Bird;
	bird_frame_provider = new BirdFrameFetch(FRAME_1, this);
	bird_frame_provider->append_src(FRAME_2);
	bird_frame_provider->resume_flow();
}

void BirdObsticals::update_frame() {
	if (auto_update_height) {
		FlyHeight current = getHeight();
		FlyHeight new_height;
		do {
			new_height = static_cast<FlyHeight>(
				QRandomGenerator::global()->bounded(HEIGHT_SIZE_TYPE_MAX));
		} while (new_height == current);
		setHeight(new_height);
	}

	if (auto_update_size) {
		BirdType current = getSize();
		BirdType new_sz;
		do {
			new_sz = static_cast<BirdType>(
				QRandomGenerator::global()->bounded(SZ_SIZE_TYPE_MAX));
		} while (new_sz == current);
		setSize(new_sz);
	}
}
