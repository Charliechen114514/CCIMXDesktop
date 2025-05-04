#pragma once

#ifdef _WIN32
#include <fstream>
#else
#include <unistd.h>
#endif

typedef struct {
	/* 3D Acceleration value */
	struct {
		float x;
		float y;
		float z;
	} g_acc;

	/* 3D Rolations dekta */
	struct {
		float x;
		float y;
		float z;
	} rol;

	float temperature;
} ICM20608AppData;

class ICM20608 {
public:
	ICM20608() = default;
	/* disable all copies then */
	ICM20608& operator=(const ICM20608&) = delete;
	ICM20608(const ICM20608&) = delete;

	/*
		invoke this to get the data, True if the data is valid
	 */
	bool get_package_sync(ICM20608AppData& empty_data_pack);

private:
	/* replace the dev file with your owns */
	static constexpr const char* _dev_file_path = "/dev/icm20608";
	/* dev file */
	void bind_dev_file();
#ifdef _WIN32
	std::ifstream dev_stream;
	bool get_package_sync_win32impl(ICM20608AppData& empty);
#else
	int private_fd { -1 };
	bool get_package_sync_uniximpl(ICM20608AppData& empty);
#endif
};
