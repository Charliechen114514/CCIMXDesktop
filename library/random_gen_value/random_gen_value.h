/**
 * @file RANDOM_GEN_VALUE_H
 * @brief Defines a templated class for generating random numbers with optional exclusion.
 */

#ifndef RANDOM_GEN_VALUE_H
#define RANDOM_GEN_VALUE_H

#include <random> // For random number generation facilities (std::random_device, std::mt19937, distributions)
#include <stdexcept> // For standard exception types (std::logic_error, std::runtime_error)
#include <type_traits> // For type traits (std::is_arithmetic_v, std::is_integral_v, std::is_floating_point_v)

/**
 * @brief A templated class for generating random numbers of a specified arithmetic type.
 *
 * This class provides static methods to generate random numbers within a given range,
 * supporting both integral and floating-point types. It also includes a method to
 * generate a random number while excluding a specific value.
 *
 * @tparam RandType The type of random number to generate. Must be an arithmetic type.
 */
template <typename RandType>
class RandomGenerator {
    /**
     * @brief Compile-time assertion to ensure RandType is an arithmetic type.
     * If RandType is not arithmetic (e.g., a custom class), a compilation error will occur.
     */
    static_assert(std::is_arithmetic_v<RandType>, "RandType must be arithmetic");

public:
    /**
     * @brief Generates a random number within a specified range [min, max].
     * 	 * This method uses `std::random_device` for non-deterministic seeding and `std::mt19937`
     * as the random number engine. It employs `std::uniform_int_distribution` for integral types
     * and `std::uniform_real_distribution` for floating-point types to ensure uniform distribution.
     * 	 * @param min The minimum possible value in the random range (inclusive).
     * @param max The maximum possible value in the random range (inclusive).
     * @return A randomly generated value of type `RandType` within the specified range.
     * @throws std::logic_error if `RandType` is not an integral or floating-point type (though
     * `static_assert` should catch this at compile time).
     */
    static RandType random(const RandType min, const RandType max) {
        if constexpr (std::is_integral_v<RandType>) {
            // Static random_device and mt19937 ensure they are initialized only once across all calls.
            static std::random_device rd; ///< Non-deterministic random number generator.
            static std::mt19937 gen(rd()); ///< Mersenne Twister engine seeded by rd.
            std::uniform_int_distribution<RandType> dis(min, max); ///< Distribution for integral types.
            return dis(gen);
        } else if constexpr (std::is_floating_point_v<RandType>) {
            // Static random_device and mt19937 ensure they are initialized only once across all calls.
            static std::random_device rd; ///< Non-deterministic random number generator.
            static std::mt19937 gen(rd()); ///< Mersenne Twister engine seeded by rd.
            std::uniform_real_distribution<RandType> dis(min, max); ///< Distribution for floating-point types.
            return dis(gen);
        } else {
            // This branch should theoretically not be reached due to static_assert.
            throw std::logic_error("Unsupported type for RandomGenerator");
        }
    }

    /**
     * @brief Generates a random number within a specified range, excluding a particular value.
     * 	 * This method repeatedly calls `random(min, max)` up to `MAX_TRY` times until a value
     * different from `except` is generated.
     * 	 * @tparam MAX_TRY The maximum number of attempts to generate a value different from `except`.
     * Defaults to 100.
     * @param min The minimum possible value in the random range (inclusive).
     * @param max The maximum possible value in the random range (inclusive).
     * @param except The value to be excluded from the generated random numbers.
     * @return A randomly generated value of type `RandType` within the specified range, not equal to `except`.
     * @throws std::logic_error if the range [min, max] only contains the `except` value, making generation impossible.
     * @throws std::runtime_error if a value different from `except` cannot be generated within `MAX_TRY` attempts.
     */
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
