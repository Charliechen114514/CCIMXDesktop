#ifndef DINASOURGAMEMAINWIDGET_H
#define DINASOURGAMEMAINWIDGET_H

#include "core/DifficultyType.h"
#include "core/ObstacleType.h"
#include <QWidget>

// Forward declarations
class ObstacleListManager;
class ScoreManager;
class FlushRequester;
class DinasourFrameFetcher;
class SoundEffectPlayer;
class Dinasour;
class EventManager;
class DifficultyManager;
class SceneDrawer;

/**
 * @class DinasourGameMainWidget
 * @brief Main game widget that manages the dinosaur game
 */
class DinasourGameMainWidget : public QWidget {
    Q_OBJECT
public:
	/**
	 * @struct CurrentInfoPack
	 * @brief Contains current game state information
	 */
	struct CurrentInfoPack {
		int score; ///< Current game score
		Difficulty t; ///< Current difficulty level
	};

	/**
	 * @brief Constructs the main game widget
	 * @param parent Parent widget
	 */
	explicit DinasourGameMainWidget(QWidget* parent = nullptr);

	/**
	 * @brief Checks if game has started
	 * @return True if game is started
	 */
	bool is_game_started() { return game_start; };

	/**
	 * @brief Checks if game is over
	 * @return True if game is over
	 */
	bool is_game_over() { return game_over; }

	/**
	 * @brief Starts the game
	 */
	void launch_game();

	/**
	 * @brief Processes jump action
	 */
	void process_jump();

	/**
	 * @brief Processes lay (duck) action
	 */
	void process_lay();

	/**
	 * @brief Gets current game information
	 * @return CurrentInfoPack containing score and difficulty
	 */
	CurrentInfoPack infoPack() const;

	/**
	 * @brief Gets dinosaur instance
	 * @return Pointer to dinosaur object
	 */
	Dinasour* get_dinasour_instance() const { return dinasour; }

signals:
	/**
	 * @brief Emitted when game starts
	 */
	void game_started();

	/**
	 * @brief Emitted when game ends
	 */
	void game_overed();

public slots:
	/**
	 * @brief Increases score based on obstacle type
	 * @param type Type of obstacle passed
	 */
	void gain_score(ObstacleType type);

	/**
	 * @brief Pauses the game
	 */
	void pause();

	/**
	 * @brief Resumes the game
	 */
	void resume();

	/**
	 * @brief Processes death event
	 */
	void process_die();

	/**
	 * @brief Resets game to initial state
	 */
	void clearAndReset();

	/**
	 * @brief Triggers lay animation
	 */
	inline void animate_lay() { process_lay(); }

	/**
	 * @brief Triggers jump animation
	 */
	void animate_up();

protected:
	/**
	 * @brief paint issue
	 * 
	 * @param event 
	 */
	void paintEvent(QPaintEvent* event) override;
	/**
	 * @brief keypress issue
	 * 
	 * @param event 
	 */
	void keyPressEvent(QKeyEvent* event) override;
	/**
	 * @brief key release issue
	 * 
	 * @param event 
	 */
	void keyReleaseEvent(QKeyEvent* event) override;
	/**
	 * @brief mouse press issue
	 * 
	 * @param event 
	 */
	void mousePressEvent(QMouseEvent* event) override;

private:
	FlushRequester* scene_flush_once; ///< Scene update requester
	Dinasour* dinasour; ///< Player dinosaur instance
	ObstacleListManager* obstacleManager; ///< Manages obstacles
	SoundEffectPlayer* soundEffectPlayer; ///< Handles sound effects
	std::shared_ptr<EventManager> eventManager; ///< Manages input events
	ScoreManager* scoreManager; ///< Manages scoring
	DifficultyManager* difficulty_manager; ///< Manages difficulty
	SceneDrawer* sceneDrawer; ///< Handles rendering
	bool game_over { false }; ///< Game over flag
	bool game_start { false }; ///< Game started flag

	/**
	 * @brief Initializes game components
	 */
	void init_memory();

	/**
	 * @brief Sets up signal-slot connections
	 */
	void init_connection();

	/**
	 * @brief Updates game state
	 */
	void update_game();
};

#endif // DINASOURGAMEMAINWIDGET_H
