#ifndef AP3216C_ADAPTER_H
#define AP3216C_ADAPTER_H
#include <string>
#include <optional>
#include "ap3216c.h"

class AP3216CAdapter {
public:
    /* provide label located in the */
    bool bind_file(const std::string& dev_file_path);
    std::optional<AP3216CData> sync_read_once(void);

private:
    std::string dev_file{};
    int private_fd{ -1 };
};

#endif
