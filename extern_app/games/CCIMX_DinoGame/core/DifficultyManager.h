#ifndef DIFFICULTYMANAGER_H
#define DIFFICULTYMANAGER_H

#include "core/DifficultyType.h"
#include <QObject>
class QTimer;
/**
 * @class DifficultyManager
 * @brief Manages game difficulty levels and their transitions
 *
 * The DifficultyManager class handles the current difficulty level of the game,
 * provides functionality to upgrade difficulty, and emits signals when difficulty
 * parameters change. It supports both manual and automatic difficulty updates.
 */
class DifficultyManager : public QObject {
    Q_OBJECT
public:
	/**
	 * @brief Constructs a DifficultyManager object
	 * @param parent The parent QObject (optional)
	 */
	explicit DifficultyManager(QObject* parent = nullptr);

	/**
	 * @brief Upgrades the game difficulty to the next level
	 *
	 * If the current difficulty is already at the highest level,
	 * this function will have no effect.
	 */
	void upgrade_difficulty();

	/**
	 * @brief Enables or disables automatic difficulty updates
	 * @param st True to enable auto-update, false to disable
	 */
	void set_auto_update(bool st);

	/**
	 * @brief Resets the difficulty to the initial level (EASY)
	 *
	 * This is a forced reset that immediately changes the difficulty
	 * regardless of any timers or auto-update settings.
	 */
	void force_reset();

	/**
	 * @brief Gets the current difficulty level
	 * @return The current Difficulty enum value
	 */
	Difficulty get_current_difficulty() const { return current_difficulty; }

signals:
	/**
	 * @brief Signal emitted when the difficulty level changes
	 * @param difficulty The new difficulty level
	 */
	void difficulty_changed(Difficulty difficulty);

	/**
	 * @brief Signal emitted when the movement speed changes
	 * @param new_speed The new movement speed value
	 */
	void new_move_speed(const int new_speed);

	/**
	 * @brief Signal emitted when the maximum obstacle count changes
	 * @param new_speed The new maximum obstacle count
	 */
	void new_obstacle_cnt_max(const int new_speed);

private slots:
	/**
	 * @brief Handles the difficulty change process
	 *
	 * This slot is triggered when the difficulty needs to be updated,
	 * either manually or through the auto-update timer.
	 */
	void process_difficulty_changed();

private:
	Difficulty current_difficulty { Difficulty::EASY }; ///< Current difficulty level
	QTimer* auto_update_timer; ///< Timer for automatic difficulty updates
};

#endif // DIFFICULTYMANAGER_H
