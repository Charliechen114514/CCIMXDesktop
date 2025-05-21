#ifndef PESUDOICM20608_H
#define PESUDOICM20608_H

#include "ICM20608Data.h"

/// @class PesudoICM20608
/// @brief Pseudo implementation of ICM20608 for testing or non-real hardware.
class PesudoICM20608 {
public:
	PesudoICM20608() = default;

	/// Disable copy assignment and copy constructor
	PesudoICM20608& operator=(const PesudoICM20608&) = delete;
	PesudoICM20608(const PesudoICM20608&) = delete;

	/// @brief Get pseudo sensor data package.
	/// @param empty_data_pack Reference to data struct to fill.
	/// @return always returns true for test data.
	bool get_package_sync(ICM20608AppData& empty_data_pack);
};

#endif // PESUDOICM20608_H
