#ifndef LEDCONTROLLER_H
#define LEDCONTROLLER_H

#ifdef USE_REAL_ADAPTER
#include "led_adapter.h"
#else
#include "PesudoLedController.h"
#endif

/// @class LEDController
/// @brief High-level controller interface for controlling LEDs, abstracting real or pseudo backends.
class LEDController {
public:
	/// @brief Default constructor.
	LEDController() = default;

	/// @brief Default destructor.
	~LEDController() = default;

	/// @brief Redirects the controller to another LED.
	/// @param ledName Name of the target LED.
	void redirectTo(const std::string& ledName) {
		ledAdapter.redirectTo(ledName);
	}

	/// @brief Returns the LED path in use.
	/// @return Path as a string.
	std::string ledPath() const { return ledAdapter.ledPath(); }

	/// @brief Sets the control mode.
	/// @param mode LED control mode.
	inline void setMode(const Modes mode) { ledAdapter.setMode(mode); }

	/// @brief Gets the current LED control mode.
	/// @return Current mode.
	inline Modes getMode() const { return ledAdapter.getMode(); }

	/// @brief Processes the LED using a parameter package.
	/// @param package Parameter package pointer.
	/// @return True if operation succeeded.
	bool processByPackage(const LEDParamsPackage* package) {
		return ledAdapter.processByPackage(package);
	}

private:
#ifdef USE_REAL_ADAPTER
	LEDAdapter ledAdapter; ///< Actual hardware adapter.
#else
	PesudoLedController ledAdapter; ///< Simulation adapter for non-hardware builds.
#endif
};

#endif // LEDCONTROLLER_H
