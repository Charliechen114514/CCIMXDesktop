#ifndef SCENEDRAWER_H
#define SCENEDRAWER_H

#include "core/DifficultyType.h"
#include <QList>
#include <QRect>

class Dinasour;
class QPainter;
class Obsticals;

/**
 * @struct GroundLineProviders
 * @brief Provides components for drawing ground lines
 */
struct GroundLineProviders;

/**
 * @class SceneDrawer
 * @brief Handles all rendering operations for the game scene
 */
class SceneDrawer {
public:
	SceneDrawer() = delete;
	/**
	 * @brief disable copy move object
	 * 
	 */
	Q_DISABLE_COPY_MOVE(SceneDrawer);

	/**
	 * @brief Constructs a SceneDrawer with specified boundaries
	 * @param sceneRect The bounding rectangle of the scene
	 */
	explicit SceneDrawer(const QRect& sceneRect);

	/**
	 * @brief Binds a QPainter for drawing operations
	 * @param p Pointer to the QPainter to use
	 */
	void bind_painter(QPainter* p);

	/**
	 * @brief Draws the sky background
	 */
	void drawSky();

	/**
	 * @brief Draws game content (score and difficulty)
	 * @param score Current game score
	 * @param type Current difficulty level
	 */
	void drawContent(int score, Difficulty type);

	/**
	 * @brief Draws the dinosaur character
	 * @param dinasour Pointer to the dinosaur object
	 */
	void drawDinasore(Dinasour* dinasour);

	/**
	 * @brief Draws all obstacles
	 * @param obs List of obstacles to draw
	 */
	void drawObstical(const QList<Obsticals*>& obs);

	/**
	 * @brief Draws the main ground line
	 */
	void drawMainGround();

	/**
	 * @brief Draws the flowing ground effect
	 * @param current_speed Current game speed
	 */
	void drawFlowyGround(int current_speed);

	/**
	 * @brief Sets whether to draw the hello message
	 * @param st True to draw hello message, false otherwise
	 */
	void setDrawHello(bool st) { drawHello = st; }

private:
	QRect sceneRect; ///< Scene boundaries rectangle
	QPainter* painter; ///< Current painter object
	bool drawHello { true }; ///< Flag for hello message visibility
	std::shared_ptr<GroundLineProviders> providers; ///< Ground line drawing components

	/**
	 * @brief Draws the sun
	 * @param center Center position of the sun
	 * @param radius Radius of the sun
	 */
	void drawSun(const QPointF& center, qreal radius);
};

#endif // SCENEDRAWER_H
