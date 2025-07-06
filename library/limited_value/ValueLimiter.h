#ifndef VALUELIMITER_H
#define VALUELIMITER_H
#include <stdexcept>
#include <utility>
using ValueLimitType = int;
using ValueLimitSimplePair = std::pair<ValueLimitType, ValueLimitType>;
namespace ValueLimitUtils {

constexpr int minFromPair(ValueLimitSimplePair p) noexcept {
    return p.first;
}
constexpr int maxFromPair(ValueLimitSimplePair p) noexcept {
    return p.second;
}

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

template <ValueLimitType MIN = 0, ValueLimitType MAX = 100>
class StaticLimiter {
    static_assert(MIN <= MAX, "MIN must be <= MAX");

public:
    constexpr ValueLimitType boundValue(ValueLimitType value) const {
        return value < MIN ? MIN : (value > MAX ? MAX : value);
    }
};

}

template <ValueLimitType MIN = 0, ValueLimitType MAX = 100>
class ValueLimiter {
public:
    ValueLimiter() = default;

    constexpr ValueLimitType boundValue(ValueLimitType value) {
        if constexpr (value < value_pair.first)
            return value_pair.first;
        else if constexpr (value > value_pair.second)
            return value_pair.second;
        return value;
    }

private:
    std::pair<ValueLimitType, ValueLimitType> value_pair {
        MIN, MAX
    };
};

#endif // VALUELIMITER_H
