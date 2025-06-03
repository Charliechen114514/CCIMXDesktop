/**
 * @class GroundLineProviders
 * @brief Provides and manages animated ground lines for the scene background.
 */

#ifndef GROUNDLINEPROVIDERS_H
#define GROUNDLINEPROVIDERS_H

#include "settings/setting_scene.h"
#include <QList>
class QPainter;

/**
 * @brief A utility class to manage and render dynamic ground lines.
 */
class GroundLineProviders {
public:
	/**
	 * @brief Deleted default constructor to enforce parameterized construction.
	 */
	GroundLineProviders() = delete;

	/**
	 * @brief Disables copy and move semantics.
	 */
	Q_DISABLE_COPY_MOVE(GroundLineProviders);

	/**
	 * @brief Constructs GroundLineProviders with line pattern length and scene height.
	 * @param patternLength The length of the line pattern.
	 * @param h The height of the scene.
	 */
	explicit GroundLineProviders(int patternLength, int h);

	/**
	 * @struct GroundLine
	 * @brief Represents a single ground line with position, length, and animation phase.
	 */
	struct GroundLine {
		int x; ///< Starting x-position of the line.
		int y0; ///< Initial vertical position.
		int length; ///< Length of the ground line.
		float phase; ///< Animation phase of the line.
	};

	/**
	 * @brief Initializes ground lines.
	 * @param count Number of lines to initialize. Default is 200.
	 */
	void initGroundLines(int count = 200);

	/**
	 * @brief Updates ground line parameters based on scrolling speed.
	 * @param scrollSpeed The horizontal scrolling speed.
	 */
	void update_params(int scrollSpeed);

	/**
	 * @brief Draws the ground lines on the given painter.
	 * @param painter The QPainter used for rendering.
	 * @param w Width of the drawing area.
	 * @param h Height of the drawing area.
	 */
	void drawLines(QPainter* painter, int w, int h);

private:
	/**
	 * @brief Horizontal scroll offset.
	 */
	int scrollOffsetX { 0 };

	/**
	 * @brief Height of the scene.
	 */
	int sceneHeight;

	/**
	 * @brief Width of the scene.
	 */
	int sceneWidth;

	/**
	 * @brief Time-based animation parameter.
	 */
	float time = 0;

	/**
	 * @brief Fixed vertical position of the ground line.
	 */
	static constexpr int groundY = Settings::Scene::Ground::GROUND_Y_POS;

	/**
	 * @brief List of all ground lines to be rendered.
	 */
	QList<GroundLine> groundLines;
};

#endif // GROUNDLINEPROVIDERS_H
