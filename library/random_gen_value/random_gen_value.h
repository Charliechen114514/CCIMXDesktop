#ifndef RANDOM_GEN_VALUE_H
#define RANDOM_GEN_VALUE_H

#include <random>
#include <stdexcept>
#include <type_traits>

template <typename RandType>
class RandomGenerator {
    static_assert(std::is_arithmetic_v<RandType>, "RandType must be arithmetic");

public:
    static RandType random(const RandType min, const RandType max) {
        if constexpr (std::is_integral_v<RandType>) {
            static std::random_device rd;
            static std::mt19937 gen(rd());
            std::uniform_int_distribution<RandType> dis(min, max);
            return dis(gen);
        } else if constexpr (std::is_floating_point_v<RandType>) {
            static std::random_device rd;
            static std::mt19937 gen(rd());
            std::uniform_real_distribution<RandType> dis(min, max);
            return dis(gen);
        } else {
            throw std::logic_error("Unsupported type for RandomGenerator");
        }
    }

    template <int MAX_TRY = 100>
    static RandType random_except(const RandType min, const RandType max, const RandType except) {
        if (min == max && min == except) {
            throw std::logic_error("Cannot generate value: only one possible value which is excluded.");
        }

        for (int i = 0; i < MAX_TRY; ++i) {
            RandType result = random(min, max);
            if (result != except)
                return result;
        }

        throw std::runtime_error("Too many attempts to generate a value different from 'except'");
    }
};

#endif // RANDOM_GEN_VALUE_H
