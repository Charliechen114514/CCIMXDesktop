#ifndef ICM20608DATA_H
#define ICM20608DATA_H

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

static constexpr const int G_MAX_VAL = 8;
static constexpr const int G_MIN_VAL = -8;
static constexpr const int ROL_MAX_VAL = 180;
static constexpr const int ROL_MIN_VAL = -180;

#endif // ICM20608DATA_H
