#ifndef PESUDOAP3216C_H
#define PESUDOAP3216C_H

#include "ap3216c.h"
#include <optional>
#include <string>

/// @class PesudoAP3216C
/// @brief Pseudo adapter that returns random AP3216C sensor data, used for simulation or testing.
class PesudoAP3216C {
public:
	/// @brief Default constructor.
	PesudoAP3216C() = default;

	/// @brief Default destructor.
	~PesudoAP3216C() = default;

	/// @brief Mocks binding to a device file.
	/// @param dev_file_path Device file path.
	/// @return Always returns true.
	bool bind_file(const std::string& dev_file_path) { return true; }

	/// @brief Returns pseudo-random sensor data.
	/// @return Optional simulated AP3216C data.
	std::optional<AP3216CData> sync_read_once(void);
};

#endif // PESUDOAP3216C_H
