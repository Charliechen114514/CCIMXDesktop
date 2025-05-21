#pragma once
#include "ICM20608Data.h"

#ifdef _WIN32
#include <fstream>
#else
#include <unistd.h>
#endif

/// @class ICM20608
/// @brief Interface class to communicate with ICM20608 sensor device.
class ICM20608 {
public:
	ICM20608() = default;

	/// Disable copy assignment and copy constructor
	ICM20608& operator=(const ICM20608&) = delete;
	ICM20608(const ICM20608&) = delete;

	/// @brief Synchronously get sensor data package.
	/// @param empty_data_pack Reference to data struct to fill.
	/// @return true if data is valid.
	bool get_package_sync(ICM20608AppData& empty_data_pack);

private:
	static constexpr const char* _dev_file_path = "/dev/icm20608"; ///< Device file path

	/// Bind the device file (platform dependent)
	void bind_dev_file();

#ifdef _WIN32
	std::ifstream dev_stream; ///< Windows device stream
	bool get_package_sync_win32impl(ICM20608AppData& empty);
#else
	int private_fd { -1 }; ///< Unix file descriptor
	bool get_package_sync_uniximpl(ICM20608AppData& empty);
#endif
};
