#ifndef FLOATSLIDEBAR_H
#define FLOATSLIDEBAR_H

#include <QSlider>

#include <QSlider>

class FloatSlider : public QSlider {
	Q_OBJECT
	static constexpr float MIN = 0.0;
	static constexpr float MAX = 100.0;
	static constexpr int PRE = 1000;

public:
	explicit FloatSlider(Qt::Orientation orientation, QWidget* parent = nullptr);
	void setFloatRange(double min, double max);
	void setFloatValue(double val);
	double floatValue() const;

signals:
	void floatValueChanged(double val);

private slots:
	void onIntValueChanged(int);

private:
	void updateSliderValue();

	double current_min { MIN };
	double current_max { MAX };
	int precision { PRE };
};

#endif // FLOATSLIDEBAR_H
