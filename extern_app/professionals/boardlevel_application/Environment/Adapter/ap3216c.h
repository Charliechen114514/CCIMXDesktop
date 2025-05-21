#ifndef AP3216C_H
#define AP3216C_H

/// @brief Invalid value constant used for AP3216C sensor readings.
#define AP3216CData_INVALID_VALUE (0)

/// @struct AP3216CData
/// @brief Stores the IR, ambient light, and proximity sensor data.
typedef struct {
	unsigned short ir; ///< Infrared data.
	unsigned short als; ///< Ambient light sensor data.
	unsigned short ps; ///< Proximity sensor data.
} AP3216CData;

/// @brief Minimum and maximum values for each sensor channel.
static constexpr unsigned int MIN_IR_VALUE { 0 };
static constexpr unsigned int MIN_ALS_VALUE { 0 };
static constexpr unsigned int MIN_PS_VALUE { 0 };
static constexpr unsigned int MAX_IR_VALUE { 1024 };
static constexpr unsigned int MAX_ALS_VALUE { 65535 };
static constexpr unsigned int MAX_PS_VALUE { 1024 };

#endif // AP3216C_H
