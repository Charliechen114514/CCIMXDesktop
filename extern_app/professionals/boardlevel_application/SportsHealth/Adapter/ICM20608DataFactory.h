#ifndef ICM20608DATAFACTORY_H
#define ICM20608DATAFACTORY_H

#ifdef USE_REAL_ADAPTER
#include "icm20608_adapter.h"
#else
#include "PesudoICM20608.h"
#endif

/* Data Factory always get data with non-platform level */
class ICM20608DataFactory {
public:
	ICM20608DataFactory() = default;
	ICM20608DataFactory& operator=(const ICM20608DataFactory&) = delete;
	ICM20608DataFactory(const ICM20608DataFactory&) = delete;
	bool get_package_sync(ICM20608AppData& empty_data_pack) {
		return icm20608_handle.get_package_sync(empty_data_pack);
	}

private:
#ifdef USE_REAL_ADAPTER
	ICM20608
#else
	PesudoICM20608
#endif
	icm20608_handle;
};

#endif // ICM20608DATAFACTORY_H
