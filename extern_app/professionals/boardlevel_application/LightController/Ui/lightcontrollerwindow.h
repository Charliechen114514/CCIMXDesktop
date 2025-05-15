#ifndef LIGHTCONTROLLERWINDOW_H
#define LIGHTCONTROLLERWINDOW_H

#include "LEDController.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class LightControllerWindow;
}
QT_END_NAMESPACE

class LightControllerWindow : public QMainWindow {
	Q_OBJECT

public:
	enum class Speed {
		Slow,
		Normal,
		Fast
	};
	static constexpr const char* DEV_FILE = "red-led";
	LightControllerWindow(QWidget* parent = nullptr);
	~LightControllerWindow();
	static constexpr const short BLINK_DEF = 500;
	void process_flip();
	void process_blink();
	void process_mode_switching();
	void process_speed_switching();

private:
	bool init_state { false };
	Ui::LightControllerWindow* ui;
	LEDController ledController;
	LEDParamsPackagePlain* plain_package { nullptr };
	LEDParamsPackageBlink* blink { nullptr };
	Speed speed { Speed::Normal };
	void init_mode();
};
#endif // LIGHTCONTROLLERWINDOW_H
