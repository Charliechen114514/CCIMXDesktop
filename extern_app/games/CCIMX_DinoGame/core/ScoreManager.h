#ifndef SCOREMANAGER_H
#define SCOREMANAGER_H

#include "settings/settings_score.h"
#include <QObject>

class QTimer;
class QMutex;

class ScoreManager : public QObject {
	Q_OBJECT
public:
	/**
	 * @brief Constructs a ScoreManager
	 * @param parent Parent QObject
	 */
	explicit ScoreManager(QObject* parent);

	/**
	 * @brief Gets current score
	 * @return Current score value
	 */
	int get_score() const { return score; }

	/**
	 * @brief Gets current score increment step
	 * @return Current step value
	 */
	int get_step() const { return step; }

public slots:
	/**
	 * @brief Sets score increment step size
	 * @param step Increment step (default: Settings::Score::DEF_STEP)
	 */
	void set_score_increase_step(int step = Settings::Score::DEF_STEP);

	/**
	 * @brief Increments score once using current step
	 */
	void increase_once();

	/**
	 * @brief Increments score by specified amount
	 * @param score Amount to increase
	 */
	void increase_once(int score);

	/**
	 * @brief Enables/disables automatic score increase
	 * @param st True to enable auto-increase
	 */
	void set_increase_automatically(bool st);

	/**
	 * @brief Resets score to initial value
	 */
	void force_reset();

private:
	int score { Settings::Score::START_SCORE }; ///< Current score value
	int step { Settings::Score::DEF_STEP }; ///< Current increment step
	std::shared_ptr<QMutex> mutex_locker; ///< Thread synchronization mutex
	QTimer* auto_update_timer; ///< Timer for automatic updates
};

#endif // SCOREMANAGER_H
