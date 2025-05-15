#ifndef AP3216C_ADAPTER_H
#define AP3216C_ADAPTER_H
#ifdef USE_REAL_ADAPTER
#include "ap3216c.h"
#include <optional>
#include <string>
class AP3216CAdapter {
public:
	/* provide label located in the */
	bool bind_file(const std::string& dev_file_path);
	std::optional<AP3216CData> sync_read_once(void);

private:
	std::string dev_file {};
	int private_fd { -1 };
};
#endif
#endif
