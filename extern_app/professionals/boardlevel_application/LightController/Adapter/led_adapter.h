/*
    This is a led adapter, which is using in
    drive the led in upper level way
*/
#ifndef LED_ADAPTER
#define LED_ADAPTER
#ifdef USE_REAL_ADAPTER
#include "LEDParamsPackage.h"
#include <string>
class LEDAdapter {
public:
    explicit LEDAdapter() = default;
	~LEDAdapter() = default;
	/* this means switching to other led */
	void redirectTo(const std::string& ledName);
	/* led written path */
	std::string ledPath() const { return led_path; }
	/* modes are set to define how to control packages */
	inline void setMode(const Modes mode) { this->mode = mode; }
	/* get the current mode */
	inline Modes getMode() const { return this->mode; }
	/* bind the package with required parameters */
	bool processByPackage(const LEDParamsPackage* package);

private:
	std::string led_path;
	Modes mode { Modes::Plain };
	/* make the real write */
	bool write_file(const std::string& fileName, const std::string& content);
};
#endif // Real Adapter
#endif
