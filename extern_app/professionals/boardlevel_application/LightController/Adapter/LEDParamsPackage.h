#ifndef LEDPARAMSPACKAGE_H
#define LEDPARAMSPACKAGE_H

enum class Modes {
	Blink, /* Trighger mode */
	Plain, /* Normal Control */
	Disabled /* disabled, this state the led is unavailable */
};

class LEDParamsPackage {
public:
	virtual ~LEDParamsPackage() = default;
};

class LEDParamsPackageBlink : public LEDParamsPackage {
public:
	static constexpr int DEFAULT_ON_TIME = 500;
	static constexpr int DEFAULT_OFF_TIME = 500;
	LEDParamsPackageBlink(int onTime, int offTime)
		: onTime(onTime)
		, offTime(offTime) { }
	int getOnTime() const { return onTime; }
	int getOffTime() const { return offTime; }
	void setOnTime(int time) { onTime = time; }
	void setOffTime(int time) { offTime = time; }

private:
	int onTime { DEFAULT_ON_TIME };
	int offTime { DEFAULT_OFF_TIME };
};

class LEDParamsPackagePlain : public LEDParamsPackage {
public:
	LEDParamsPackagePlain(bool isOn)
		: isOn(isOn) { }
	bool getIsOn() const { return isOn; }
	void setIsOn(bool isOn) { this->isOn = isOn; }

private:
	bool isOn { false };
};

#endif // LEDPARAMSPACKAGE_H
