#ifndef OBSTACLELISTMANAGER_H
#define OBSTACLELISTMANAGER_H

#include "core/ObstacleType.h"
#include <QObject>

class Obsticals;
class CactusObsticals;
class BirdObsticals;
class QMutex;
class Dinasour;

/**
 * @class ObstacleListManager
 * @brief Manages the creation, rendering, and collision detection of obstacles
 */
class ObstacleListManager : public QObject {
    Q_OBJECT
public:
	/**
	 * @brief Constructs an ObstacleListManager
	 * @param parent Parent QObject
	 */
	explicit ObstacleListManager(QObject* parent = nullptr);

	/**
	 * @brief Gets obstacles that should be rendered
	 * @return List of active obstacles
	 */
	QList<Obsticals*> get_should_render();

	/**
	 * @brief Initializes the obstacle system
	 */
	void start_blank_working();

	/**
	 * @brief Performs one animation frame update
	 */
	void animate_once();

	/**
	 * @brief Resets all obstacles to initial state
	 */
	void reset_back();

	/**
	 * @brief Checks for collision with dinosaur
	 * @param dinasour Pointer to dinosaur object
	 * @return True if collision detected
	 */
	bool is_intersects(Dinasour* dinasour);

	/**
	 * @brief Gets all obstacle pools
	 * @return List of all obstacle instances
	 */
	QList<Obsticals*> get_pools();

	/**
	 * @brief Sets maximum number of active obstacles
	 * @param max_count Maximum obstacle count
	 */
	void set_max_obstacle_cnt(short max_count);

	/**
	 * @brief Gets maximum obstacle count
	 * @return Current maximum obstacle count
	 */
	int max_obstacle_cnt() const { return obs_max_count; }

	/**
	 * @brief Gets count of active obstacles
	 * @return Number of currently active obstacles
	 */
	int activate_obstacle_cnt() const { return activate_obsticals.size(); }

	/**
	 * @brief Gets current obstacle movement speed
	 * @return Current speed value
	 */
	int get_obstacle_speed();

signals:
	/**
	 * @brief Emitted when an obstacle is passed
	 * @param type Type of obstacle passed
	 * @param which Specific obstacle instance
	 */
	void pass_a_obstacle(ObstacleType type, Obsticals* which);

public slots:
	/**
	 * @brief Updates active obstacles
	 */
	void flush_activate_obsticals_once();

	/**
	 * @brief Sets obstacle movement speed
	 * @param speed New speed value
	 */
	void set_obstacle_speed(int speed);

private:
	/// @brief Mutex for thread safety
	std::shared_ptr<QMutex> locker;

	/// @brief List of currently active obstacles
	QList<Obsticals*> activate_obsticals;

	/// @brief Pool of cactus obstacles
	QList<CactusObsticals*> cactus_obsticals_pool;

	/// @brief Pool of bird obstacles
	QList<BirdObsticals*> brid_obsticals_pool;

	/// @brief Maximum allowed active obstacles
	int obs_max_count;

	/**
	 * @enum BaseType
	 * @brief Types of obstacles
	 */
	enum class BaseType {
		Cactus, ///< Cactus type obstacle
		Bird ///< Bird type obstacle
	};

	/**
	 * @brief Gets inactive obstacles of specified type
	 * @param t Type of obstacles to query
	 * @param how_many Number of obstacles needed
	 * @return List of available obstacles
	 */
	QList<Obsticals*> query_unactivates(BaseType t, int how_many);

	/**
	 * @brief Initializes obstacle pools
	 */
	void init_instance_pool();

	/**
	 * @brief Handles obstacle passing logic
	 */
	void process_internal_pass_session();

	/**
	 * @brief Randomly generates new obstacles
	 */
	void process_random_summon_once();

	/**
	 * @brief Gets rightmost position of active obstacles
	 * @return Maximum x-coordinate
	 */
	int get_max_right_x_of_actives() const;

	/**
	 * @brief Adjusts positions for new obstacles
	 * @param new_members New obstacles to add
	 * @param start_x Starting x-coordinate
	 * @return Adjusted starting position
	 */
	int adjustif_new_members(const QList<Obsticals*>& new_members, int start_x);

	/**
	 * @brief Enables bird obstacles
	 */
	void let_bird_appear() { should_bird_appear = true; }

	/// @brief Flag indicating if birds should appear
	bool should_bird_appear { false };
};

#endif // OBSTACLELISTMANAGER_H
