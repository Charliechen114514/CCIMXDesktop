#ifndef SPORTSHEALTHWINDOW_H
#define SPORTSHEALTHWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class SportsHealthWindow;
}
QT_END_NAMESPACE

/**
 * @class SportsHealthWindow
 * @brief Main window for sports health monitoring application.
 *
 * This window coordinates UI and sensor data updates,
 * including refresh frequency for live data display.
 */
class SportsHealthWindow : public QMainWindow {
    Q_OBJECT

public:
	static constexpr int FLUSH_FREQ = 1000; ///< Refresh frequency in milliseconds

	/**
	 * @brief Constructs the SportsHealthWindow.
	 * @param parent Parent widget pointer.
	 */
	SportsHealthWindow(QWidget* parent = nullptr);

	/**
	 * @brief Destructor for SportsHealthWindow.
	 */
	~SportsHealthWindow();

private:
	Ui::SportsHealthWindow* ui;
};

#endif // SPORTSHEALTHWINDOW_H
