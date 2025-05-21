#ifndef ICM20608_H
#define ICM20608_H

#define AP3216CData_INVALID_VALUE (0)
/**
 * @brief ICM20608Data is a data structure for ICM20608 data
 *        which is supposed to be query from driver, see CCIMXBase:
 *        https://github.com/Charliechen114514/CCIMXBase/tree/driver/drivers for
 *        details
 */
typedef struct {
	/* 3D Acceleration value */
	struct {
		int x;
		int y;
		int z;
	} g_acc;

	/* 3D Rolations dekta */
	struct {
		int x;
		int y;
		int z;
	} rol;
	/* chips internal temp */
	int temperature;
} ICM20608Data;

#endif
