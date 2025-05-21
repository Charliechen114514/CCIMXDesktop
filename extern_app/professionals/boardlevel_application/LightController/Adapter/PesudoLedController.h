#ifndef PESUDOLEDCONTROLLER_H
#define PESUDOLEDCONTROLLER_H

#include "LEDParamsPackage.h"
#include <string>

/// @class PesudoLedController
/// @brief Simulated LED controller used when real hardware is not available.
class PesudoLedController {
public:
	/// @brief Default constructor.
	PesudoLedController() = default;

	/// @brief Default destructor.
	~PesudoLedController() = default;

	/// @brief Redirects to another LED (no-op in simulation).
	/// @param ledName LED identifier.
	void redirectTo(const std::string& ledName) { (void)ledName; }

	/// @brief Returns the (simulated) LED path.
	/// @return Fake path string.
	std::string ledPath() const { return led_path; }

	/// @brief Sets the control mode.
	/// @param mode Control mode.
	inline void setMode(const Modes mode) { this->mode = mode; }

	/// @brief Gets the current control mode.
	/// @return Current mode.
	inline Modes getMode() const { return this->mode; }

	/// @brief Processes the parameter package (always succeeds in simulation).
	/// @param package LED parameter package.
	/// @return Always true.
	bool processByPackage(const LEDParamsPackage* package) { return true; }

private:
	std::string led_path; ///< Path string for LED (not used in pseudo).
	Modes mode { Modes::Plain }; ///< Operating mode.
};

#endif // PESUDOLEDCONTROLLER_H
