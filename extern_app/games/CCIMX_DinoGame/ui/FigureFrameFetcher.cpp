#include "FigureFrameFetcher.h"
#include "settings/settings_figure.h"
DinasourFrameFetcher::DinasourFrameFetcher(
    const QString& valid_base_path, QObject* parent)
    : FrameProvider(valid_base_path, parent) {
    using namespace Settings::Figure::Dinasour;
    src_rect = QRect(X, Y, WIDTH, HEIGHT); // normal
}

QRect& DinasourFrameFetcher::src_bounding_rect() {
	using namespace Settings::Figure::Dinasour;
	switch (s) {
	case State::NORMAL:
		src_rect.setSize({ WIDTH, HEIGHT });
		break;
	case State::LAY:
		src_rect.setSize({ static_cast<int>(WIDTH * 1.5), static_cast<int>(HEIGHT / 1.5) });
		break;
	}
	return src_rect;
}

CactusFrameFetch::CactusFrameFetch(const QString& valid_base_path, QObject* parent)
	: ObstacleBaseFrameFetch(valid_base_path, parent) {
	using namespace Settings::Figure::Cactus;
	src_rect = QRect(X, Y, WIDTH, HEIGHT);
}

ObstacleBaseFrameFetch::ObstacleBaseFrameFetch(const QString& valid_base_path, QObject* parent)
	: FrameProvider(valid_base_path, parent) {
}

BirdFrameFetch::BirdFrameFetch(const QString& valid_base_path, QObject* parent)
	: ObstacleBaseFrameFetch(valid_base_path, parent) {
	using namespace Settings::Figure::Bird;
	src_rect = QRect(X, Y, WIDTH, HEIGHT);
}
