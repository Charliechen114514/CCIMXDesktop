#ifndef PESUDOLEDCONTROLLER_H
#define PESUDOLEDCONTROLLER_H
#include "LEDParamsPackage.h"
#include <string>
class PesudoLedController {
public:
	PesudoLedController() = default;
	~PesudoLedController() = default;
	/* this means switching to other led */
	void redirectTo(const std::string& ledName) { (void)ledName; }
	/* led written path */
	std::string ledPath() const { return led_path; }
	/* modes are set to define how to control packages */
	inline void setMode(const Modes mode) { this->mode = mode; }
	/* get the current mode */
	inline Modes getMode() const { return this->mode; }
	/* bind the package with required parameters */
	bool processByPackage(const LEDParamsPackage* package) { return true; }

private:
	std::string led_path;
	Modes mode { Modes::Plain };
};

#endif // PESUDOLEDCONTROLLER_H
