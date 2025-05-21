#ifndef ICM20608DATA_H
#define ICM20608DATA_H

/// @brief Processed sensor data with float values.
typedef struct {
	/// 3D acceleration values in float
	struct {
		float x;
		float y;
		float z;
	} g_acc;

	/// 3D rotation delta values in float
	struct {
		float x;
		float y;
		float z;
	} rol;

	float temperature; ///< Temperature value
} ICM20608AppData;

/// Constants defining valid data range
static constexpr const int G_MAX_VAL = 8;
static constexpr const int G_MIN_VAL = -8;
static constexpr const int ROL_MAX_VAL = 180;
static constexpr const int ROL_MIN_VAL = -180;

#endif // ICM20608DATA_H
