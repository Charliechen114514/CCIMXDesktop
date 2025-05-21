#ifndef ICM20608DATAFACTORY_H
#define ICM20608DATAFACTORY_H

#ifdef USE_REAL_ADAPTER
#include "icm20608_adapter.h"
#else
#include "PesudoICM20608.h"
#endif

/// @class ICM20608DataFactory
/// @brief Abstracts the real or pseudo adapter to provide sensor data.
class ICM20608DataFactory {
public:
	ICM20608DataFactory() = default;

	/// Disable copy assignment and copy constructor
	ICM20608DataFactory& operator=(const ICM20608DataFactory&) = delete;
	ICM20608DataFactory(const ICM20608DataFactory&) = delete;

	/// @brief Get sensor data package synchronously.
	/// @param empty_data_pack Reference to data struct to fill.
	/// @return true if data is valid.
	bool get_package_sync(ICM20608AppData& empty_data_pack) {
		return icm20608_handle.get_package_sync(empty_data_pack);
	}

private:
#ifdef USE_REAL_ADAPTER
	ICM20608 icm20608_handle;
#else
	PesudoICM20608 icm20608_handle;
#endif
};

#endif // ICM20608DATAFACTORY_H
