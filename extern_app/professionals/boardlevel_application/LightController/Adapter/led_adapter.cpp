#ifdef USE_REAL_ADAPTER
#include "led_adapter.h"
#include <fstream>
#include <iostream>

namespace {
/* compose the path here */
std::string composePath(const std::string& ledName) {
	return "/sys/class/leds/" + ledName + "/";
}
}

void LEDAdapter::redirectTo(const std::string& ledName) {
	this->led_path = composePath(ledName);
}

bool LEDAdapter::processByPackage(const LEDParamsPackage* package) {
	bool operations = false;
	switch (mode) {
	case Modes::Blink: {
		const LEDParamsPackageBlink* blink = dynamic_cast<const LEDParamsPackageBlink*>(package);
		if (!blink)
			return false;
		/* set to the blink mode */
		operations = write_file(led_path + "trigger", "timer");
		/* set the on off time */
		operations &= write_file(led_path + "delay_on", std::to_string(blink->getOnTime()));
		operations &= write_file(led_path + "delay_off", std::to_string(blink->getOffTime()));
		break;
	} break;
	case Modes::Plain: {
		const LEDParamsPackagePlain* plain = dynamic_cast<const LEDParamsPackagePlain*>(package);
		if (!plain)
			return false;
		/* set to the plain mode */
		operations = write_file(led_path + "trigger", "none");
		/* set the level */
		operations &= write_file(led_path + "brightness",
								 plain->getIsOn() ? "1" : "0");
		break;
	} break;
	default:
		break;
	}
	return operations;
}

bool LEDAdapter::write_file(const std::string& fileName, const std::string& content) {
	std::ofstream file(fileName);
	if (!file.is_open()) {
		std::cerr << "Failed to open file: " << fileName << std::endl;
		return false;
	}
	file << content;

	if (file.fail()) {
		std::cerr << "Failed to write to file: " << fileName << std::endl;
		return false;
	}

	if (file.bad()) {
		std::cerr << "Error writing to file: " << fileName << std::endl;
		return false;
	}
	return true;
}
#endif
