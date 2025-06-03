#ifndef OBSTICALS_H
#define OBSTICALS_H

#include "figure/FigureObject.h"
#include "settings/setting_scene.h"

class QMutex;
class Dinasour;
class CactusFrameFetch;

/**
 * @class Obsticals
 * @brief Base class for all obstacle objects in the game
 */
class Obsticals : public FigureObject {
	Q_OBJECT
	Q_PROPERTY(int moving_speed READ get_moving_speed WRITE set_moving_speed NOTIFY speedChanged)

public:
	/**
	 * @brief Constructs an Obsticals object
	 * @param parent Parent QObject
	 */
	explicit Obsticals(QObject* parent = nullptr);

	/**
	 * @brief Default virtual destructor
	 */
	virtual ~Obsticals() = default;

	/**
	 * @brief Checks collision with dinosaur
	 * @param dinasour Pointer to dinosaur object
	 * @return True if collision detected
	 */
	virtual bool is_intersect(Dinasour* dinasour);

	/**
	 * @brief Gets current moving speed
	 * @return Current speed value
	 */
	int get_moving_speed() const { return moving_speed; }

	/**
	 * @brief Updates obstacle position
	 */
	virtual void update_position();

	/**
	 * @brief Provides collision bounding rectangle (pure virtual)
	 * @return Reference to current QRect
	 */
	virtual QRect& provide_current_bounding_rect() = 0;

	/**
	 * @brief Provides drawing frame (pure virtual)
	 * @return Reference to current QPixmap
	 */
	virtual QPixmap& provide_drawing_srcframe() = 0;

signals:
	/**
	 * @brief Emitted when obstacle passes out of view
	 */
	void pass_me_already();

	/**
	 * @brief Emitted when speed changes
	 * @param newSpeed New speed value
	 */
	void speedChanged(int newSpeed);

public slots:
	/**
	 * @brief Sets moving speed
	 * @param speed New speed value
	 */
	virtual void set_moving_speed(const int speed);

protected:
	std::shared_ptr<QMutex> mutex; ///< Mutex for thread safety
	int moving_speed { Settings::Scene::Difficulty::DEF_SPEED }; ///< Current movement speed
};

#endif // OBSTICALS_H
