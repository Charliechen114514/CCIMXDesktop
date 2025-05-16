#ifndef PESUDOICM20608_H
#define PESUDOICM20608_H
#include "ICM20608Data.h"
class PesudoICM20608 {
public:
	PesudoICM20608() = default;
	PesudoICM20608& operator=(const PesudoICM20608&) = delete;
	PesudoICM20608(const PesudoICM20608&) = delete;

	bool get_package_sync(ICM20608AppData& empty_data_pack);
};

#endif // PESUDOICM20608_H
