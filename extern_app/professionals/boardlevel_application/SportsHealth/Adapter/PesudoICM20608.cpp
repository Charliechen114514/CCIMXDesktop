#include "PesudoICM20608.h"
#include <random>
namespace {

float random_float(const float min, const float max) {
	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::uniform_real_distribution<float> dis(min, max);
	return dis(gen);
}

}

bool PesudoICM20608::get_package_sync(ICM20608AppData& empty_data_pack) {
	/* randomly get the Numbers */
	empty_data_pack.rol.x = random_float(ROL_MIN_VAL, ROL_MAX_VAL);
	empty_data_pack.rol.y = random_float(ROL_MIN_VAL, ROL_MAX_VAL);
	empty_data_pack.rol.z = random_float(ROL_MIN_VAL, ROL_MAX_VAL);
	empty_data_pack.g_acc.x = random_float(G_MIN_VAL, G_MAX_VAL);
	empty_data_pack.g_acc.y = random_float(G_MIN_VAL, G_MAX_VAL);
	empty_data_pack.g_acc.z = random_float(G_MIN_VAL, G_MAX_VAL);
	empty_data_pack.temperature = random_float(20, 25);
	return true;
}
