#include "SceneDrawer.h"
#include "core/DifficultyType.h"
#include "figure/dinasour/Dinasour.h"
#include "figure/obstacle/Obsticals.h"
#include "settings/setting_scene.h"
#include "ui/GroundLineProviders.h"
#include <QPainter>
#include <QRandomGenerator>
SceneDrawer::SceneDrawer(const QRect& sceneRect) {
	this->sceneRect = sceneRect;
	providers = std::make_shared<GroundLineProviders>(sceneRect.width(), sceneRect.height());
	providers->initGroundLines();
}

void SceneDrawer::bind_painter(QPainter* p) {
	painter = p;
}

void SceneDrawer::drawSky() {
	using namespace Settings::Scene::Ground;
	QLinearGradient skyGradient(0, 0, 0, GROUND_Y_POS);
	skyGradient.setColorAt(0.0, QColor(0xb3e5fc));
	skyGradient.setColorAt(1.0, Qt::white);
	painter->fillRect(0, 0, sceneRect.width(), GROUND_Y_POS, skyGradient);
	QPoint sunCenter(80, 80);
	int sunRadius = 40;
	drawSun(sunCenter, sunRadius);
}

void SceneDrawer::drawSun(const QPointF& center, qreal radius) {
	QRadialGradient outerGlow(center, radius * 3, center);
	outerGlow.setColorAt(0.0, QColor(255, 255, 255, 80)); ///< 中心白色，稍微透明
	outerGlow.setColorAt(1.0, QColor(255, 255, 255, 0)); ///< 渐变到透明
	painter->setBrush(outerGlow);
	painter->setPen(Qt::NoPen);
	painter->drawEllipse(center, radius * 3, radius * 3);

	QRadialGradient midGlow(center, radius * 2, center);
	midGlow.setColorAt(0.0, QColor(255, 255, 160, 150)); ///< 柔黄
	midGlow.setColorAt(1.0, QColor(255, 255, 160, 0)); ///< 渐隐
	painter->setBrush(midGlow);
	painter->drawEllipse(center, radius * 2, radius * 2);

	// Step 3: 绘制核心太阳球体（真实颜色渐变）
	QRadialGradient sunCore(center, radius, center);
	sunCore.setColorAt(0.0, QColor(255, 255, 180)); ///< 中心稍白
	sunCore.setColorAt(0.6, QColor(255, 200, 0)); ///< 中段亮黄
	sunCore.setColorAt(1.0, QColor(255, 140, 0)); ///< 边缘橙黄
	painter->setBrush(sunCore);
	painter->drawEllipse(center, radius, radius);
}

void SceneDrawer::drawContent(int score, Difficulty diff) {
	QFont font = painter->font();
	font.setPointSize(18);
	painter->setFont(font);
	QFontMetrics fm(painter->font());
	if (drawHello) {
		QString hello_text = "Press Space / Mouse Click To Start the game!";
		auto text_width = fm.horizontalAdvance(hello_text);
		auto text_height = fm.height();
		painter->drawText(
			sceneRect.width() / 2 - text_width / 2,
			sceneRect.height() / 2 - text_height / 2,
			hello_text);
	}

	QString score_text = QString("Score: %1").arg(score);

	int score_text_width = fm.horizontalAdvance(score_text);
	constexpr int margin = 10;
	int current_draw_offset = sceneRect.width() - score_text_width - margin;
	painter->drawText(
		current_draw_offset, 20, score_text);
	QString diff_text = "Diff: ";
	switch (diff) {
	case Difficulty::EASY:
		diff_text += "Easy";
		break;
	case Difficulty::MEDIUM:
		diff_text += "OK";
		break;
	case Difficulty::HARD:
		diff_text += "Hard";
		break;
	case Difficulty::HOLY_SHIT:
		diff_text += "What the fuck";
		break;
	}
	int diff_text_width = fm.horizontalAdvance(diff_text);
	current_draw_offset -= (margin + diff_text_width);
	painter->drawText(
		current_draw_offset, 20, diff_text);
}

void SceneDrawer::drawDinasore(Dinasour* dinasour) {
	painter->drawPixmap(dinasour->provide_current_bounding_rect(),
						dinasour->provide_drawing_srcframe());
}

void SceneDrawer::drawObstical(const QList<Obsticals*>& obs) {
	for (auto& each : obs) {
		painter->drawPixmap(each->provide_current_bounding_rect(),
							each->provide_drawing_srcframe());
	}
}

void SceneDrawer::drawMainGround() {
	using namespace Settings::Scene::Ground;
	QPen pen(Qt::black);
	pen.setWidth(GROUND_PEN_WIDTH);
	painter->setPen(pen);
	int width = sceneRect.width();
	painter->drawLine(0, GROUND_Y_POS, width, GROUND_Y_POS);
	QLinearGradient groundGradient(0, GROUND_Y_POS, 0, sceneRect.height());
	groundGradient.setColorAt(0.0, QColor(0xfff9c4));
	groundGradient.setColorAt(1.0, QColor(0xf0e68c));
	painter->fillRect(0, GROUND_Y_POS, width, sceneRect.height() - GROUND_Y_POS, groundGradient);
}

void SceneDrawer::drawFlowyGround(int current_speed) {
	painter->setPen(QPen(Qt::darkGray, 1));
	if (current_speed != 0) {
		current_speed += 3;
	}
	providers->update_params(current_speed);
	int w = sceneRect.width();
	int h = sceneRect.height();
	providers->drawLines(painter, w, h);
}
