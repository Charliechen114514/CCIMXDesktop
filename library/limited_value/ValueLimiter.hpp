#ifndef VALUELIMITER_H
#define VALUELIMITER_H

#include <stdexcept>
#include <utility>

using ValueLimitType = int; /**< Type used for limit values */
using ValueLimitSimplePair = std::pair<ValueLimitType, ValueLimitType>; /**< Pair representing min/max bounds */

/**
 * @namespace ValueLimitUtils
 * @brief Utility functions for working with value limits
 */
namespace ValueLimitUtils {

/**
 * @brief Gets the minimum value from a pair
 * @param p The min/max pair
 * @return The first element (minimum) of the pair
 */
constexpr int minFromPair(ValueLimitSimplePair p) noexcept {
    return p.first;
}

/**
 * @brief Gets the maximum value from a pair
 * @param p The min/max pair
 * @return The second element (maximum) of the pair
 */
constexpr int maxFromPair(ValueLimitSimplePair p) noexcept {
    return p.second;
}

/**
 * @brief Checks if a value is within bounds
 * @param value The value to check
 * @param p The min/max bounds pair
 * @return true if value is within bounds, false otherwise
 */
constexpr bool inBound(ValueLimitType value, ValueLimitSimplePair p) {
    return value >= minFromPair(p) && value <= maxFromPair(p);
}

/**
 * @brief Clamps a value to the specified bounds
 * @param value The value to clamp
 * @param vp The min/max bounds pair
 * @return The clamped value
 * @throws std::logic_error if min > max in the bounds pair
 */
constexpr ValueLimitType boundWithPair(const ValueLimitType value,
                                       const ValueLimitSimplePair vp) {
    if (vp.first > vp.second)
        throw std::logic_error("boundWithPair: min > max");
    if (value < vp.first)
        return vp.first;
    if (value > vp.second)
        return vp.second;
    return value;
}

/**
 * @class StaticLimiter
 * @brief Compile-time value limiter with fixed bounds
 * @tparam MIN The minimum bound (default 0)
 * @tparam MAX The maximum bound (default 100)
 */
template <ValueLimitType MIN = 0, ValueLimitType MAX = 100>
class StaticLimiter {
    static_assert(MIN <= MAX, "MIN must be <= MAX");

public:
    /**
     * @brief Clamps a value to the static bounds
     * @param value The value to clamp
     * @return The clamped value
     */
    static constexpr ValueLimitType boundValue(ValueLimitType value) {
        return value < MIN ? MIN : (value > MAX ? MAX : value);
    }
};
}

/**
 * @class ValueLimiter
 * @brief Runtime-configurable value limiter with compile-time defaults
 * @tparam MIN Default minimum bound (default 0)
 * @tparam MAX Default maximum bound (default 100)
 */
template <ValueLimitType MIN = 0, ValueLimitType MAX = 100>
class ValueLimiter {
public:
    /**
     * @brief Default constructor using template bounds
     */
    ValueLimiter() = default;

    /**
     * @brief Construct with runtime-specified bounds
     * @param runtime_min The minimum bound
     * @param runtime_max The maximum bound
     */
    constexpr ValueLimiter(ValueLimitType runtime_min, ValueLimitType runtime_max) {
        setMin(runtime_min);
        setMax(runtime_max);
    }

    /**
     * @brief Gets the current minimum bound
     * @return The minimum bound value
     */
    constexpr ValueLimitType getMin() const noexcept {
        return runtime_min_;
    }

    /**
     * @brief Gets the current maximum bound
     * @return The maximum bound value
     */
    constexpr ValueLimitType getMax() const noexcept {
        return runtime_max_;
    }

    /**
     * @brief Sets the minimum bound
     * @param v The new minimum value
     * @note Automatically adjusts if new min would exceed current max
     */
    void setMin(ValueLimitType v) {
        if (v > runtime_max_)
            runtime_min_ = runtime_max_;
        else
            runtime_min_ = v;
    }

    /**
     * @brief Sets the maximum bound
     * @param v The new maximum value
     * @note Automatically adjusts if new max would be less than current min
     */
    void setMax(ValueLimitType v) {
        if (v < runtime_min_)
            runtime_max_ = runtime_min_;
        else
            runtime_max_ = v;
    }

    static constexpr ValueLimitType compileMin = MIN; /**< Compile-time minimum bound */
    static constexpr ValueLimitType compileMax = MAX; /**< Compile-time maximum bound */

    /**
     * @brief Clamps a value to the current bounds
     * @param value The value to clamp
     * @return The clamped value
     */
    constexpr ValueLimitType boundValue(ValueLimitType value) const {
        if (value < runtime_min_)
            return runtime_min_;
        if (value > runtime_max_)
            return runtime_max_;
        return value;
    }

private:
    ValueLimitType runtime_min_ = MIN; /**< Current minimum bound */
    ValueLimitType runtime_max_ = MAX; /**< Current maximum bound */
};

#endif // VALUELIMITER_H
