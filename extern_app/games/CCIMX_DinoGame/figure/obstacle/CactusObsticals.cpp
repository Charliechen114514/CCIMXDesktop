#include "CactusObsticals.h"
#include "FigureFrameFetcher.h"
#include "settings/settings_figure.h"
#include <QMutex>
#include <QRandomGenerator>
CactusObsticals::CactusObsticals(QObject* parent) {
	init_memory();
	// everytime we pass, we shell switch a new(oh, possiblly)
	// a new faces!
	connect(this, &CactusObsticals::pass_me_already,
            this, &CactusObsticals::update_frame);
}

void CactusObsticals::setSize(Size s) {
	QMutexLocker l(mutex.get());
	this->size = s;
	auto& src_frame = cactus_frame_provider->src_bounding_rect();
	using namespace Settings::Figure::Cactus;
	QSize new_size;
	int new_base;
	switch (size) {
	case Size::SMALL:
		new_base = SMALL_BASE_Y_POS;
        new_size = { CactusSZ_SMALL.width, CactusSZ_SMALL.height };
		break;
	case Size::MEDIUM:
		new_base = MED_BASE_Y_POS;
        new_size = { CactusSZ_MED.width, CactusSZ_MED.height };
		break;
	case Size::LARGE:
		new_base = LARGE_BASE_Y_POS;
        new_size = { CactusSZ_LARGE.width, CactusSZ_LARGE.height };
		break;
	}
	src_frame.setTop(new_base);
	src_frame.setSize(new_size);
}

QRect& CactusObsticals::provide_current_bounding_rect() {
	return cactus_frame_provider->src_bounding_rect();
}

QPixmap& CactusObsticals::provide_drawing_srcframe() {
	return cactus_frame_provider->src_pixmap();
}

void CactusObsticals::init_memory() {
	using namespace Settings::Figure;
	using namespace Settings::Scene;
	cactus_frame_provider = new CactusFrameFetch(Cactus::FRAME_1, this);
	QStringList bonus_frame { Cactus::FRAME_2, Cactus::FRAME_3, Cactus::FRAME_4 };
	cactus_frame_provider->append_srcs(bonus_frame);
}

void CactusObsticals::update_frame() {
	if (auto_update_sz) {
		Size new_sz = static_cast<Size>(QRandomGenerator::global()->bounded(SIZE_TYPE_MAX));
		setSize(new_sz);
	}

	cactus_frame_provider->manual_shuffle_once();
}
