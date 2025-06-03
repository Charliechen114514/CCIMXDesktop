#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

class QKeyEvent;
class QMouseEvent;
class DinasourGameMainWidget;

/**
 * @class EventManager
 * @brief Handles and processes user input events for the game
 *
 * The EventManager class processes keyboard and mouse events, translating them
 * into game actions and indications. It acts as an intermediary between
 * Qt's input system and the game logic.
 */
class EventManager {
public:
	/**
	 * @brief Enumeration of possible game actions from key presses
	 */
	enum class Indication {
		NOTHING, ///< No action indicated
		JUMP, ///< Jump action requested
		LAY, ///< Duck/lay down action requested
		LAUNCH_GAME ///< Start game action requested
	};

	/**
	 * @brief Enumeration of possible game actions from key releases
	 */
	enum class KeyReleaseIndication {
		NOTHING, ///< No action indicated
		RELAX ///< Release current action (e.g., stand up from ducking)
	};

	/**
	 * @brief Deleted default constructor
	 *
	 * EventManager must be constructed with a parent widget reference
	 */
	EventManager() = delete;

	/**
	 * @brief Constructs an EventManager with a parent widget
	 * @param h Pointer to the main game widget that owns this manager
	 */
	explicit EventManager(DinasourGameMainWidget* h) {
		holdings = h;
	}

	/**
	 * @brief Processes a key press event
	 * @param keyEvent The Qt key event to process
	 *
	 * Translates key presses into game actions and updates the current indication
	 */
	void install_keyPress_keyEvent(QKeyEvent* keyEvent);

	/**
	 * @brief Processes a key release event
	 * @param keyEvent The Qt key event to process
	 *
	 * Translates key releases into game actions and updates the release indication
	 */
	void install_keyRelease_keyEvent(QKeyEvent* keyEvent);

	/**
	 * @brief Processes a mouse press event
	 * @param mouseEvent The Qt mouse event to process
	 */
	void install_mousepress_event(QMouseEvent* mouseEvent);

	/**
	 * @brief Gets the current action indication from key presses
	 * @return The current Indication value
	 */
	inline Indication indication() const { return ind; }

	/**
	 * @brief Gets the current action indication from key releases
	 * @return The current KeyReleaseIndication value
	 */
	inline KeyReleaseIndication release_indication() const { return release_ind; }

private:
	DinasourGameMainWidget* holdings; ///< Pointer to the main game widget
	Indication ind; ///< Current action from key presses
	KeyReleaseIndication release_ind; ///< Current action from key releases
};

#endif // EVENTMANAGER_H
