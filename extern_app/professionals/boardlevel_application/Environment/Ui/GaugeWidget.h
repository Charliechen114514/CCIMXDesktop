#ifndef GaugeWidget_H
#define GaugeWidget_H
#include <QWidget>

/*
 * GaugeWidget is a base widget
 */
class GaugeWidget : public QWidget {
	Q_OBJECT
	Q_PROPERTY(double value
				   READ value
					   WRITE setValue
						   NOTIFY valueChanged)
public:
	/* default settings */
	static constexpr int DEF_MIN_VALUE { 0 };
	static constexpr int DEF_MAX_VALUE { 100 };
	static constexpr short TITLE_FONT_SZ { 12 };
	static constexpr short CURVAL_FOUT_SZ { 10 };
	static constexpr int ANIMATION_DURATION { 500 };
	static constexpr float WIDGET_MIN_WIDTH { 200 };
	static constexpr float WIDGET_MIN_HEIGHT { 200 };

	/* board color settings */
	static constexpr QColor BOARD_COLOR = QColor(160, 160, 160);
	static constexpr QColor FROM_BOARD_COLOR = QColor(190, 190, 190);
	static constexpr QColor TO_BOARD_COLOR = QColor(110, 110, 110);
	static constexpr short BOARD_LEN = 1;

	/* board draw angles */
	static constexpr short START_ANGLE { 225 };
	static constexpr short TOTAL_ANGLE { 270 };

	/* Color Gradients */
	static constexpr short COLOR_GRAD_WIDTH { 8 };
	static constexpr short COLOR_RADIUS { 90 };
	static constexpr QColor START_COLOR = QColor(255, 0, 0);
	static constexpr QColor END_COLOR = QColor(0, 255, 0);

	/* Ticks Settings */
	static constexpr int TICK_CNT { 55 };
	static constexpr short MAIN_TICK_WIDTH { 2 };
	static constexpr short SUB_TICK_WIDTH { 1 };
	static constexpr short MAIN_TICK_LENGTH { 8 };
	static constexpr short SUB_TICK_LENGTH { 5 };
	static constexpr short SUB_MAIN_RATE { 5 }; /* each 5 owns a main */
	static constexpr QColor TICK_COLOR = QColor(255, 255, 255);

	/* labels settings */
	static constexpr short LABEL_FONT_SZ { 6 };
	static constexpr QColor LABEL_COLOR = QColor(255, 255, 255);

	/* For animations, we need the property settings */
	explicit GaugeWidget(QWidget* parent = nullptr);
	/* set the range simply */
	void setRange(int min, int max) {
		max_value = max;
		min_value = min;
		update();
	}
	void setTitle(const QString& title) {
		this->title = title;
		update();
	}
	void setUnit(const QString& unit) {
		this->unit = unit;
		update();
	}
	inline double value() const { return current_value; }
	void update_value(const double value);
signals:
	void valueChanged(double value);

protected:
	/* draw behaviour at here */
	void paintEvent(QPaintEvent* event) override;

private:
	double max_value { DEF_MIN_VALUE };
	double min_value { DEF_MAX_VALUE };

	double current_value;
	/* display property */
	QFont title_font { "Arial", TITLE_FONT_SZ, QFont::Bold };
	QFont value_font { "Arial", CURVAL_FOUT_SZ, QFont::Bold };
	QFont label_font { "Arial", LABEL_FONT_SZ };
	/* display strings */
	QString title;
	QString unit;

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
