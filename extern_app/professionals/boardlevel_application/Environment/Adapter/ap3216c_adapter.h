#ifndef AP3216C_ADAPTER_H
#define AP3216C_ADAPTER_H

#ifdef USE_REAL_ADAPTER

#include "ap3216c.h"
#include <optional>
#include <string>

/// @class AP3216CAdapter
/// @brief Provides access to the real AP3216C device for sensor data retrieval.
class AP3216CAdapter {
public:
	/// @brief Binds the adapter to a device file.
	/// @param dev_file_path Path to the device file.
	/// @return True if successful, false otherwise.
	bool bind_file(const std::string& dev_file_path);

	/// @brief Reads the sensor data once from the device.
	/// @return Optional sensor data, empty if reading fails.
	std::optional<AP3216CData> sync_read_once(void);

private:
	std::string dev_file {}; ///< Path to the bound device file.
	int private_fd { -1 }; ///< File descriptor of the device file.
};

#endif // USE_REAL_ADAPTER

#endif // AP3216C_ADAPTER_H
