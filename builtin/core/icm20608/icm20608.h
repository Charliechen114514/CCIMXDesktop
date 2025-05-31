#ifndef ICM20608_H
#define ICM20608_H

/**
 * @file ICM20608.h
 * @brief Definitions for ICM20608 inertial measurement unit (IMU) sensor data
 */

/**
 * @def AP3216CData_INVALID_VALUE
 * @brief Default value indicating invalid sensor reading
 * @note This appears to be a legacy definition (AP3216C is a different sensor)
 *       Consider using ICM20608-specific naming if this is meant for ICM20608
 */
#define AP3216CData_INVALID_VALUE (0)

/**
 * @struct ICM20608Data
 * @brief Data structure containing raw sensor readings from ICM20608 device
 *
 * This structure holds 3D acceleration data, 3D rotation delta values,
 * and temperature reading from the ICM20608 sensor. All values are in raw
 * sensor units and may require conversion to standard units.
 *
 * @see CCIMXBase driver implementation:
 * https://github.com/Charliechen114514/CCIMXBase/tree/driver/drivers
 */
typedef struct {
    /**
     * @struct g_acc
     * @brief 3D acceleration values in raw sensor units
     * @note Conversion to m/s² or g-forces typically required
     */
    struct {
        int x; /**< Raw acceleration along X-axis */
        int y; /**< Raw acceleration along Y-axis */
        int z; /**< Raw acceleration along Z-axis */
    } g_acc; ///< acc

    /**
     * @struct rol
     * @brief 3D rotation delta values in raw sensor units
     * @note Conversion to degrees or radians typically required
     * @warning Possible typo in field name ("rol" instead of "rot"?)
     */
    struct {
        int x; /**< Raw rotation delta around X-axis */
        int y; /**< Raw rotation delta around Y-axis */
        int z; /**< Raw rotation delta around Z-axis */
    } rol; ///< rotations

    /**
     * @brief Chip internal temperature in raw sensor units
     * @note Conversion to Celsius or Fahrenheit typically required
     */
    int temperature;
} ICM20608Data;

#endif /* ICM20608_H */