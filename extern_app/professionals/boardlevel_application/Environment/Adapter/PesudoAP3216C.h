#ifndef PESUDOAP3216C_H
#define PESUDOAP3216C_H
#include "ap3216c.h"
#include <optional>
#include <string>
class PesudoAP3216C {
public:
	/* persudo means it actually returns random value */
	PesudoAP3216C() = default;
	~PesudoAP3216C() = default;
	/* provide a random file read */
	bool bind_file(const std::string& dev_file_path) { return true; }
	std::optional<AP3216CData> sync_read_once(void);
};

#endif // PESUDOAP3216C_H
