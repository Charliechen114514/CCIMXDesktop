/*
    This is a led adapter, which is using in
    drive the led in upper level way
*/

#ifndef LED_ADAPTER
#define LED_ADAPTER

#ifdef USE_REAL_ADAPTER

#include "LEDParamsPackage.h"
#include <string>

/// @class LEDAdapter
/// @brief Provides hardware access for controlling LEDs using parameters.
class LEDAdapter {
public:
	/// @brief Default constructor.
	explicit LEDAdapter() = default;

	/// @brief Default destructor.
	~LEDAdapter() = default;

	/// @brief Redirects the adapter to control a different LED.
	/// @param ledName Name of the LED to redirect to.
	void redirectTo(const std::string& ledName);

	/// @brief Gets the current LED path.
	/// @return String path to the LED control interface.
	std::string ledPath() const { return led_path; }

	/// @brief Sets the control mode of the LED.
	/// @param mode The control mode to set.
	inline void setMode(const Modes mode) { this->mode = mode; }

	/// @brief Gets the current LED control mode.
	/// @return The currently active mode.
	inline Modes getMode() const { return this->mode; }

	/// @brief Processes the LED using a parameter package.
	/// @param package Pointer to the LEDParamsPackage.
	/// @return True if the processing succeeded.
	bool processByPackage(const LEDParamsPackage* package);

private:
	std::string led_path; ///< Filesystem path to the LED.
	Modes mode { Modes::Plain }; ///< Current operating mode of the LED.

	/// @brief Internal method to write content to a control file.
	/// @param fileName Name of the control file.
	/// @param content Content to write.
	/// @return True on success, false on failure.
	bool write_file(const std::string& fileName, const std::string& content);
};

#endif // USE_REAL_ADAPTER

#endif // LED_ADAPTER
