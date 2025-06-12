#ifndef FLOATSLIDEBAR_H
#define FLOATSLIDEBAR_H

#include <QSlider>

/**
 * @brief The FloatSlider class
 * A QSlider subclass that allows working with floating point ranges and values.
 */
class FloatSlider : public QSlider {
    Q_OBJECT

    /// Default minimum float value
    static constexpr float MIN = 0.0;

    /// Default maximum float value
    static constexpr float MAX = 100.0;

    /// Default precision factor used to map float to int
    static constexpr int PRE = 1000;

public:
    /**
     * @brief Construct a new FloatSlider object
     * @param orientation The orientation of the slider (horizontal or vertical)
     * @param parent The parent widget, or nullptr if none
     */
    explicit FloatSlider(Qt::Orientation orientation, QWidget* parent = nullptr);

    /**
     * @brief Set the floating point range for the slider
     * @param min The minimum float value
     * @param max The maximum float value
     */
    void setFloatRange(double min, double max);

    /**
     * @brief Set the current floating point value
     * @param val The float value to set
     */
    void setFloatValue(double val);

    /**
     * @brief Get the current floating point value
     * @return Current float value
     */
    double floatValue() const;

signals:
    /**
     * @brief Signal emitted when the float value changes
     * @param val The new float value
     */
    void floatValueChanged(double val);

private slots:
    /**
     * @brief Internal slot to respond to int value changes
     * @param value New integer value
     */
    void onIntValueChanged(int value);

private:
    /**
     * @brief Update internal integer value based on current float value
     */
    void updateSliderValue();

    /// Current minimum float value
    double current_min { MIN };

    /// Current maximum float value
    double current_max { MAX };

    /// Precision factor for float-to-int mapping
    int precision { PRE };
};

#endif // FLOATSLIDEBAR_H
