#ifndef GaugeWidget_H
#define GaugeWidget_H

#include <QWidget>

/**
 * @class GaugeWidget
 * @brief A customizable gauge widget for displaying numeric values.
 *
 * This widget provides a circular gauge with configurable range,
 * title, unit, and smooth animated value updates. It supports drawing
 * ticks, labels, needle, and gradient arcs.
 */
class GaugeWidget : public QWidget {
	Q_OBJECT
	Q_PROPERTY(double value
				   READ value
					   WRITE setValue
						   NOTIFY valueChanged)

public:
	/// Default minimum value of the gauge
	static constexpr int DEF_MIN_VALUE { 0 };

	/// Default maximum value of the gauge
	static constexpr int DEF_MAX_VALUE { 100 };

	/// Font size for the title text
	static constexpr short TITLE_FONT_SZ { 12 };

	/// Font size for the current value text
	static constexpr short CURVAL_FOUT_SZ { 10 };

	/// Duration of animation in milliseconds
	static constexpr int ANIMATION_DURATION { 500 };

	/// Minimum widget width
	static constexpr float WIDGET_MIN_WIDTH { 200 };

	/// Minimum widget height
	static constexpr float WIDGET_MIN_HEIGHT { 200 };

	/// Base color for the gauge board
	static constexpr QColor BOARD_COLOR = QColor(160, 160, 160);

	/// Gradient start color for board
	static constexpr QColor FROM_BOARD_COLOR = QColor(190, 190, 190);

	/// Gradient end color for board
	static constexpr QColor TO_BOARD_COLOR = QColor(110, 110, 110);

	/// Width of the board outline
	static constexpr short BOARD_LEN = 1;

	/// Start angle for gauge drawing (degrees)
	static constexpr short START_ANGLE { 225 };

	/// Total sweep angle of gauge arc (degrees)
	static constexpr short TOTAL_ANGLE { 270 };

	/// Width of the color gradient arc
	static constexpr short COLOR_GRAD_WIDTH { 8 };

	/// Radius for the gradient arc
	static constexpr short COLOR_RADIUS { 90 };

	/// Gradient start color for the gauge arc
	static constexpr QColor START_COLOR = QColor(255, 0, 0);

	/// Gradient end color for the gauge arc
	static constexpr QColor END_COLOR = QColor(0, 255, 0);

	/// Total number of ticks on the gauge
	static constexpr int TICK_CNT { 55 };

	/// Width of main ticks
	static constexpr short MAIN_TICK_WIDTH { 2 };

	/// Width of sub ticks
	static constexpr short SUB_TICK_WIDTH { 1 };

	/// Length of main ticks
	static constexpr short MAIN_TICK_LENGTH { 8 };

	/// Length of sub ticks
	static constexpr short SUB_TICK_LENGTH { 5 };

	/// Number of sub ticks per main tick
	static constexpr short SUB_MAIN_RATE { 5 };

	/// Color of the ticks
	static constexpr QColor TICK_COLOR = QColor(255, 255, 255);

	/// Font size for labels on ticks
	static constexpr short LABEL_FONT_SZ { 6 };

	/// Color for labels
	static constexpr QColor LABEL_COLOR = QColor(255, 255, 255);

	/**
	 * @brief Constructor.
	 * @param parent Parent widget pointer.
	 */
	explicit GaugeWidget(QWidget* parent = nullptr);

	/**
	 * @brief Set the gauge range.
	 * @param min Minimum value.
	 * @param max Maximum value.
	 */
	void setRange(int min, int max) {
		max_value = max;
		min_value = min;
		update();
	}

	/**
	 * @brief Set the title text displayed on the gauge.
	 * @param title Gauge title.
	 */
	void setTitle(const QString& title) {
		this->title = title;
		update();
	}

	/**
	 * @brief Set the unit text displayed with the value.
	 * @param unit Unit string.
	 */
	void setUnit(const QString& unit) {
		this->unit = unit;
		update();
	}

	/**
	 * @brief Get the current gauge value.
	 * @return Current value.
	 */
	inline double value() const { return current_value; }

	/**
	 * @brief Update the gauge value with optional animation.
	 * @param value New value to display.
	 */
	void update_value(const double value);

signals:
	/**
	 * @brief Signal emitted when the gauge value changes.
	 * @param value The new value.
	 */
	void valueChanged(double value);

protected:
	/**
	 * @brief Paint event handler to render the gauge.
	 * @param event Paint event.
	 */
	void paintEvent(QPaintEvent* event) override;

private:
	double max_value { DEF_MIN_VALUE }; ///< Maximum value of gauge
	double min_value { DEF_MAX_VALUE }; ///< Minimum value of gauge
	double current_value; ///< Current displayed value

	QFont title_font { "Arial", TITLE_FONT_SZ, QFont::Bold }; ///< Font for title
	QFont value_font { "Arial", CURVAL_FOUT_SZ, QFont::Bold }; ///< Font for value
	QFont label_font { "Arial", LABEL_FONT_SZ }; ///< Font for tick labels

	QString title; ///< Title text to display
	QString unit; ///< Unit text to display

	/**
	 * @brief Set the value internally and emit signals.
	 * @param val New value to set.
	 */
	void setValue(const double val) {
		if (qFuzzyCompare(current_value, val))
			return;
		current_value = val;
		emit valueChanged(val);
		update();
	}

	void drawBackground(QPainter& p);
	void drawArc(QPainter& p);
	void drawTicks(QPainter& p);
	void drawLabels(QPainter& p);
	void drawNeedle(QPainter& p);
	void drawCenter(QPainter& p);
	void drawTexts(QPainter& p);
};

#endif
