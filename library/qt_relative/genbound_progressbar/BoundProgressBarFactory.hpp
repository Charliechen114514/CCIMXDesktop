#ifndef BOUNDPROGRESSBARFACTORY_H
#define BOUNDPROGRESSBARFACTORY_H

#include "library/limited_value/ValueLimiter.hpp"
#include <QObject>
#include <QSlider>

/**
 * @class BoundSliderFactory
 * @brief Factory class for creating bounded QSlider widgets
 *
 * This template class provides a convenient way to create and manage QSlider widgets
 * with enforced value boundaries. It handles value clamping and synchronization between
 * the internal state and the actual QSlider widget.
 *
 * @tparam default_value The default value for the slider (must be within min/max bounds)
 * @tparam min The minimum allowed value (default 0)
 * @tparam max The maximum allowed value (default 100)
 */
template <ValueLimitType default_value, ValueLimitType min = 0, ValueLimitType max = 100>
class BoundSliderFactory : public QObject {
    static_assert(ValueLimitUtils::inBound(default_value, { min, max }),
                  "Default Value is MisMatch");

public:
    /**
     * @brief Constructs a BoundSliderFactory instance
     * @param barWidget Pointer to the QSlider widget to manage
     * @param parent Parent QObject (optional)
     */
    explicit BoundSliderFactory(QSlider* barWidget, QObject* parent = nullptr)
        : QObject(parent)
        , monitoring_bar(barWidget) {
        monitoring_bar->setMaximum(max);
        monitoring_bar->setMinimum(min);
        monitoring_bar->setValue(current_value);
        connect(monitoring_bar, &QSlider::valueChanged, this, [this](int value) {
            _plain_set_value(value);
        });
    }

    /**
     * @brief Gets the current slider value
     * @return The current bounded value
     */
    inline int queryValue() const { return current_value; }

    /**
     * @brief Sets the slider value (with bounds enforcement)
     * @param value The new value to set
     */
    void inline setValue(int value) {
        _plain_set_value(value);
        monitoring_bar->setValue(current_value);
    }

protected:
    /**
     * @brief Internal method for setting values with bounds checking
     * @param value The value to set
     * @note This method handles the actual bounds enforcement and is used
     *       to work around Q_OBJECT limitations in template classes
     */
    virtual void _plain_set_value(int value) {
        current_value = ValueLimitUtils::StaticLimiter<min, max>::boundValue(value);
    }

    int current_value { default_value }; /**< The current bounded value */
    QSlider* monitoring_bar; /**< Pointer to the managed QSlider widget */
};

#endif // BOUNDPROGRESSBARFACTORY_H
