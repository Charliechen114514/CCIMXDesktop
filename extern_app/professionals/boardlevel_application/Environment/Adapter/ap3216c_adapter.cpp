#include "ap3216c_adapter.h"
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <iostream>
bool AP3216CAdapter::bind_file(const std::string& file)
{
    private_fd = ::open(file.c_str(), O_RDONLY);
    std::cerr << private_fd << "got!\n";
    return private_fd >= 0;
}

std::optional<AP3216CData> AP3216CAdapter::sync_read_once(void)
{
    if(private_fd < 0) return std::nullopt;

    AP3216CData data{};
    ssize_t n = ::read(private_fd, &data, sizeof(data));

    if (n == sizeof(data)) {
        return data;
    } else if (n == 0) {
        std::cerr << "read returned 0, device probably not ready\n";
        return std::nullopt;
    } else if (n < 0) {
        std::cerr << "read error: " << strerror(errno) << std::endl;
    } else {
        std::cerr << "partial read (" << n << " bytes), discarding\n";
        return std::nullopt;
    }

    ::close(private_fd);
    private_fd = -1;
    return std::nullopt;
}
