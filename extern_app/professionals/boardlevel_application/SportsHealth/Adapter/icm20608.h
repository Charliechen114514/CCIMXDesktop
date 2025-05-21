#ifndef ICM20608_H
#define ICM20608_H

#define AP3216CData_INVALID_VALUE (0)

/// @brief Raw sensor data from ICM20608 device.
typedef struct {
	/// 3D acceleration values
	struct {
		int x;
		int y;
		int z;
	} g_acc;

	/// 3D rotation delta values
	struct {
		int x;
		int y;
		int z;
	} rol;

	int temperature; ///< Temperature reading
} ICM20608Data;

#endif // ICM20608_H
