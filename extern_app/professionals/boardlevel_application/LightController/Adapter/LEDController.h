#ifndef LEDCONTROLLER_H
#define LEDCONTROLLER_H
#ifdef USE_REAL_ADAPTER
#include "led_adapter.h"
#else
#include "PesudoLedController.h"
#endif

class LEDController {
public:
    LEDController() = default;
	~LEDController() = default;
	/* this means switching to other led */
	void redirectTo(const std::string& ledName) {
		ledAdapter.redirectTo(ledName);
	}
	/* led written path */
	std::string ledPath() const { return ledAdapter.ledPath(); }
	/* modes are set to define how to control packages */
	inline void setMode(const Modes mode) { ledAdapter.setMode(mode); }
	/* get the current mode */
	inline Modes getMode() const { return ledAdapter.getMode(); }
	/* bind the package with required parameters */
	bool processByPackage(const LEDParamsPackage* package) {
		return ledAdapter.processByPackage(package);
	}

private:
#ifdef USE_REAL_ADAPTER
	LEDAdapter ledAdapter;
#else
	PesudoLedController ledAdapter;
#endif
};

#endif // LEDCONTROLLER_H
