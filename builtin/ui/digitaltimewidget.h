#ifndef DIGITALTIMEWIDGET_H
#define DIGITALTIMEWIDGET_H
#include <QTime>
#include <QWidget>
class ClockWidget;
/**
 * @brief The DigitalTimeWidget class is a digital clock widget
 */
class DigitalTimeWidget : public QWidget {
    Q_OBJECT
public:
	/**
	 * @brief Construct a new Digital Time Widget object
	 * 
	 * @param parent 
	 */
	explicit DigitalTimeWidget(QWidget* parent = nullptr);
	/**
	 * @brief bindClockWidget, the digital displays of the clock
	 * @param clock widgets for the bindings
	 */
	void bindClockWidget(ClockWidget* clock);
public slots:
	/**
	 * @brief process_time_update: process the time update sessions from
	 * clock widgets
	 * @param process_time
	 */
	void process_time_update(QTime process_time);

protected:
	/**
	 * @brief paint sessions
	 * 
	 * @param event 
	 */
	void paintEvent(QPaintEvent* event) override;

private:
	QTime stored_time; ///< handle time
	ClockWidget* clk_widget { nullptr }; ///< clk widgets holdings
};

#endif // DIGITALTIMEWIDGET_H
