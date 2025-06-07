#include "FloatSlideBar.h"

FloatSlider::FloatSlider(Qt::Orientation orientation, QWidget* parent)
	: QSlider(orientation, parent) {
	setRange(0, precision);
	connect(this, &QSlider::valueChanged,
			this, &FloatSlider::onIntValueChanged);
}

void FloatSlider::setFloatRange(double min, double max) {
	current_min = min;
	current_max = max;
	updateSliderValue();
}

void FloatSlider::setFloatValue(double val) {
	val = qBound(current_min, val, current_max);
	int intVal = static_cast<int>((val - current_min) / (current_max - current_min) * precision);
	/* prevent the wrong signals emit */
	blockSignals(true);
	setValue(intVal);
	blockSignals(false);
	emit floatValueChanged(val);
}

double FloatSlider::floatValue() const {
	return current_min + (value() / static_cast<double>(precision)) * (current_max - current_min);
}

void FloatSlider::onIntValueChanged(int) {
	emit floatValueChanged(floatValue());
}

void FloatSlider::updateSliderValue() {
	setFloatValue(floatValue());
}
