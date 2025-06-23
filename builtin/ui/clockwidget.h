#ifndef CLOCKWIDGET_H
#define CLOCKWIDGET_H
#include <QTime>
#include <QWidget>

namespace Ui {
class ClockWidget;
}
class QTimer;

/**
 * @brief The ClockWidget class draws the Clock Sessions
 */
class ClockWidget : public QWidget {
    Q_OBJECT

public:
	/**
     * @brief Construct a new Clock Widget object
     *
     * @param parent
     */
	explicit ClockWidget(QWidget* parent = nullptr);
	/**
	 * @brief Destroy the Clock Widget object
     *
	 */
	~ClockWidget();
public slots:
    /**
     * @brief timeout hooks of the internal_updater
     */
    void process_update_invokation(QTime clockTime);

protected:
	/* Yep, for the dynamic widgets, we have to, sadly, draw by ourselves */
	/* Entry for us to draw a clock */

	/**
	 * @brief paintEvent the event everytime mainWidgets hopes to draw
	 * @param _paintEvent the event handle posts from the parent
	 */
	void paintEvent(QPaintEvent* _paintEvent) override;
	/**
	 * @brief sizeHint provides the size hint for the clock widget
	 * @return yet the size :)
	 */
	QSize sizeHint() const override;

private:
	// Constants
	static constexpr const int DefaultWidgetSize = 1000;
	static constexpr const int DialSize = 200;
	static constexpr const int OuterCircleRadius = 95;
	static constexpr const int HourTickLength = 10;
	static constexpr const int MinuteTickLength = 5;
	static constexpr const int HourTickWidth = 2;
	static constexpr const int MinuteTickWidth = 1;
	static constexpr const int CenterDotRadius = 4;
	static constexpr const int HourHandLength = 50;
	static constexpr const int MinuteHandLength = 70;
	static constexpr const int SecondHandLength = 80;
	static constexpr const int HandWidth = 7;
	static constexpr const int HourRotationPerHour = 30; // 360 / 12
	static constexpr const int MinuteRotationPerMinute = 6; // 360 / 60
	static constexpr const int SecondRotationPerSecond = 6; // 360 / 60

	/* fonts */
	static constexpr const int NumberDistanceFromCenter = 70;
	static constexpr const int NumberFontSize = 14;
	Ui::ClockWidget* ui;
    QTime cur_time;
	/* paintEvent periodly and invoke the funcList in sequence */
	void drawBackground(QPainter* painter);
	void drawTicks(QPainter* painter);
	void drawHands(QPainter* painter);
	void drawNumbers(QPainter* painter);
	void drawCenterDot(QPainter* painter);
};

#endif // CLOCKWIDGET_H
