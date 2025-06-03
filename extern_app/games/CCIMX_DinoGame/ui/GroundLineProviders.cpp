#include "GroundLineProviders.h"
#include "settings/setting_scene.h"
#include <QPainter>
#include <QRandomGenerator>
using namespace Settings::Scene::BackGround::RandomLine;

GroundLineProviders::GroundLineProviders(int patternLength, int h) {
	this->sceneWidth = patternLength;
	this->sceneHeight = h;
}

void GroundLineProviders::initGroundLines(int count) {
	groundLines.clear();
	for (int i = 0; i < count; ++i) {
		GroundLine line;
		line.x = QRandomGenerator::global()->bounded(sceneWidth);
		line.y0 = QRandomGenerator::global()->bounded(groundY + 2, sceneHeight);
		line.length = QRandomGenerator::global()->bounded(minLineLength, maxLineLength);
		line.phase = QRandomGenerator::global()->generateDouble() * phaseMax;
		groundLines.append(line);
	}
}

void GroundLineProviders::update_params(int scrollSpeed) {
	if (scrollSpeed == 0) {
		return;
	}
	scrollOffsetX = (scrollOffsetX + scrollSpeed) % sceneWidth;
	time += Settings::Scene::SCENE_FLUSH_HZ / 1000.0;
}

void GroundLineProviders::drawLines(QPainter* painter, int w, int h) {
	for (const auto& line : std::as_const(groundLines)) {
		int x = line.x - scrollOffsetX;

		while (x < w) {
			if (x + line.length >= 0) {
				// get the y offset
				float offsetY = qSin(time * timeFrequency + line.phase) * oscillationAmplitude;
				int y = qBound(yOffsetMin, int(line.y0 + offsetY), h - 1);
				painter->drawLine(x, y, x + line.length, y);
			}
			x += sceneWidth;
		}
	}
}
