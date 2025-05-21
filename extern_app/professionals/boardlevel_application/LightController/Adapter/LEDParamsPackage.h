#ifndef LEDPARAMSPACKAGE_H
#define LEDPARAMSPACKAGE_H

/// @enum Modes
/// @brief Represents the control mode of an LED.
enum class Modes {
	Blink, ///< LED will blink based on on/off timing.
	Plain, ///< LED is controlled directly (on/off).
	Disabled ///< LED is disabled and unavailable.
};

/// @class LEDParamsPackage
/// @brief Base class for LED parameter packages.
class LEDParamsPackage {
public:
	/// @brief Virtual destructor.
	virtual ~LEDParamsPackage() = default;
};

/// @class LEDParamsPackageBlink
/// @brief Parameter package for blinking LED behavior.
class LEDParamsPackageBlink : public LEDParamsPackage {
public:
	static constexpr int DEFAULT_ON_TIME = 500; ///< Default ON time in milliseconds.
	static constexpr int DEFAULT_OFF_TIME = 500; ///< Default OFF time in milliseconds.

	/// @brief Constructor with on/off timing.
	/// @param onTime ON duration in ms.
	/// @param offTime OFF duration in ms.
	LEDParamsPackageBlink(int onTime, int offTime)
		: onTime(onTime)
		, offTime(offTime) { }

	int getOnTime() const { return onTime; } ///< Gets ON time.
	int getOffTime() const { return offTime; } ///< Gets OFF time.
	void setOnTime(int time) { onTime = time; } ///< Sets ON time.
	void setOffTime(int time) { offTime = time; } ///< Sets OFF time.

private:
	int onTime { DEFAULT_ON_TIME }; ///< Time LED stays ON.
	int offTime { DEFAULT_OFF_TIME }; ///< Time LED stays OFF.
};

/// @class LEDParamsPackagePlain
/// @brief Parameter package for simple on/off LED control.
class LEDParamsPackagePlain : public LEDParamsPackage {
public:
	/// @brief Constructor.
	/// @param isOn Initial on/off state.
	LEDParamsPackagePlain(bool isOn)
		: isOn(isOn) { }

	bool getIsOn() const { return isOn; } ///< Gets the on/off state.
	void setIsOn(bool isOn) { this->isOn = isOn; } ///< Sets the on/off state.

private:
	bool isOn { false }; ///< Whether the LED is on.
};

#endif // LEDPARAMSPACKAGE_H
