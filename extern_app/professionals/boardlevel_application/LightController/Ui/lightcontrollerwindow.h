#ifndef LIGHTCONTROLLERWINDOW_H
#define LIGHTCONTROLLERWINDOW_H

#include "LEDController.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class LightControllerWindow;
}
QT_END_NAMESPACE

/// @class LightControllerWindow
/// @brief Main window class for controlling LEDs with various modes and speeds.
class LightControllerWindow : public QMainWindow {
	Q_OBJECT

public:
	/// @brief Enumeration for LED blinking speed.
	enum class Speed {
		Slow, ///< Slow blinking speed
		Normal, ///< Normal blinking speed
		Fast ///< Fast blinking speed
	};

	/// @brief Device file identifier for the red LED.
	static constexpr const char* DEV_FILE = "red-led";

	/// @brief Default blink interval in milliseconds.
	static constexpr const short BLINK_DEF = 500;

	/// @brief Constructor.
	/// @param parent Parent widget.
	LightControllerWindow(QWidget* parent = nullptr);

	/// @brief Destructor.
	~LightControllerWindow();

	/// @brief Handle flipping the LED state.
	void process_flip();

	/// @brief Handle blinking the LED.
	void process_blink();

	/// @brief Switch the LED operation mode.
	void process_mode_switching();

	/// @brief Switch the blinking speed.
	void process_speed_switching();

private:
	bool init_state { false }; ///< Indicates whether initialization has completed.
	Ui::LightControllerWindow* ui; ///< Pointer to UI elements.
	LEDController ledController; ///< Controller object for LED operations.
	LEDParamsPackagePlain* plain_package { nullptr }; ///< Parameters for plain LED mode.
	LEDParamsPackageBlink* blink { nullptr }; ///< Parameters for blink mode.
	Speed speed { Speed::Normal }; ///< Current blinking speed.

	/// @brief Initialize LED mode settings.
	void init_mode();
};

#endif // LIGHTCONTROLLERWINDOW_H
