#pragma once

// Platform-specific includes
#ifdef _WIN32
#include <fstream>  // Windows file handling
#else
#include <unistd.h>  // UNIX file handling
#endif

/**
 * @struct ICM20608AppData
 * @brief Data structure containing sensor readings from ICM20608 device
 * 
 * This structure holds 3D acceleration data, 3D rotation delta values,
 * and temperature reading from the ICM20608 sensor.
 */
typedef struct {
    /* 3D Acceleration values */
    struct {
        float x;  ///< Acceleration along X-axis (in g units)
        float y;  ///< Acceleration along Y-axis (in g units)
        float z;  ///< Acceleration along Z-axis (in g units)
    } g_acc; ///< acc

    /* 3D Rotation delta values */
    struct {
        float x;  ///< Rotation delta around X-axis (in degrees)
        float y;  ///< Rotation delta around Y-axis (in degrees)
        float z;  ///< Rotation delta around Z-axis (in degrees)
    } rol; ///< rotations

    float temperature;  ///< Temperature reading from sensor (in Celsius)
} ICM20608AppData;

/**
 * @class ICM20608
 * @brief Interface for ICM20608 inertial measurement unit (IMU) sensor
 * 
 * This class provides platform-agnostic access to ICM20608 sensor data,
 * with implementations for both Windows and UNIX-like systems.
 */
class ICM20608 {
public:
    /**
     * @brief Default constructor
     * @note Uses compiler-generated default implementation
     */
    ICM20608() = default;

    // Disable copy operations to ensure single ownership of device resource
    ICM20608& operator=(const ICM20608&) = delete;  ///< Deleted copy assignment
    ICM20608(const ICM20608&) = delete;             ///< Deleted copy constructor

    /**
     * @brief Synchronously reads sensor data package
     * @param empty_data_pack Reference to data structure to be filled with sensor readings
     * @return true if data was successfully read and is valid, false otherwise
     * 
     * @note This is the main interface method for getting sensor data
     */
    bool get_package_sync(ICM20608AppData& empty_data_pack);

private:
    /// Device file path (Linux) - should be replaced with actual device path
    static constexpr const char* _dev_file_path = "/dev/icm20608";

    /**
     * @brief Binds to the device file
     * @note Called internally when first accessing the device
     */
    void bind_dev_file();

    // Platform-specific implementations
#ifdef _WIN32
    std::ifstream dev_stream;  ///< Windows file stream for device access
    
    /**
     * @brief Windows-specific implementation of sensor data reading
     * @param empty Reference to data structure to be filled
     * @return true if successful, false otherwise
     */
    bool get_package_sync_win32impl(ICM20608AppData& empty);
#else
    int private_fd { -1 };  ///< UNIX file descriptor (initialized to invalid)
    
    /**
     * @brief UNIX-specific implementation of sensor data reading
     * @param empty Reference to data structure to be filled
     * @return true if successful, false otherwise
     */
    bool get_package_sync_uniximpl(ICM20608AppData& empty);
#endif
};