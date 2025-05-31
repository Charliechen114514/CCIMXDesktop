/*
    Adapter file of the icm20608
*/
#include "icm20608_adapter.h"
#include "icm20608.h"
#include <fcntl.h>
#include <iostream>
/**
 * @brief ICM20608::bind_dev_file
 * bind dev file makes to open the dev file as
 * expected
 */
void ICM20608::bind_dev_file() {
#ifdef _WIN32
	dev_stream.open(_dev_file_path, std::ios::binary);
#else
	/* bind the file */
	private_fd = ::open(_dev_file_path, O_RDONLY);
#endif
}

#ifdef _WIN32
/**
 * @brief As the name goes, invoke this make a synchronous request
 * to the device
 *
 * @param   empty is means the params is empty or wait be written,
 *          or, its a output params
 * @return  true if the data is valid(session request success equavalent)
 */
bool ICM20608::get_package_sync_win32impl(ICM20608AppData& empty) {
	if (!dev_stream.is_open()) {
		bind_dev_file();
		if (!dev_stream.is_open()) {
			return false;
		}
	}

	ICM20608Data icm_data;
	dev_stream.read(reinterpret_cast<char*>(&icm_data), sizeof(ICM20608Data));

	if (dev_stream.gcount() != sizeof(ICM20608Data)) {
		return false;
	}

	empty.rol.x = static_cast<float>(icm_data.rol.x) / 16.4f;
	empty.rol.y = static_cast<float>(icm_data.rol.y) / 16.4f;
	empty.rol.z = static_cast<float>(icm_data.rol.z) / 16.4f;
	empty.g_acc.x = static_cast<float>(icm_data.g_acc.x) / 2048.0f;
	empty.g_acc.y = static_cast<float>(icm_data.g_acc.y) / 2048.0f;
	empty.g_acc.z = static_cast<float>(icm_data.g_acc.z) / 2048.0f;
	empty.temperature = (static_cast<float>(icm_data.temperature) - 25.0f) / 326.8f + 25.0f;

	return true;
}

#else
/**
 * @brief Unix Implementations of sync request
 * @param empty is means the params is empty or wait be written,
 *          or, its a output params
 * @return  true if the data is valid(session request success equavalent)
 */
bool ICM20608::get_package_sync_uniximpl(ICM20608AppData& empty) {
	if (private_fd == -1) {
		bind_dev_file();
		if (private_fd == -1) {
			return false; // try again failed
		}
	}

	ICM20608Data icm_data;
	ssize_t ret = ::read(private_fd, &icm_data, sizeof(ICM20608Data));
	(void)ret;
	/* raw data */
	empty.rol.x = (float)(icm_data.rol.x) / 16.4f;
	empty.rol.y = (float)(icm_data.rol.y) / 16.4f;
	empty.rol.z = (float)(icm_data.rol.z) / 16.4f;
	empty.g_acc.x = (float)(icm_data.g_acc.x) / 2048.0f;
	empty.g_acc.y = (float)(icm_data.g_acc.y) / 2048.0f;
	empty.g_acc.z = (float)(icm_data.g_acc.z) / 2048.0f;

	empty.temperature = ((float)(icm_data.temperature) - 25.0f) / 326.8f + 25.0f;
	return true;
}
#endif

bool ICM20608::get_package_sync(ICM20608AppData& empty_data_pack) {
#ifdef _WIN32
	return get_package_sync_win32impl(empty_data_pack);
#else
	return get_package_sync_uniximpl(empty_data_pack);
#endif
}
