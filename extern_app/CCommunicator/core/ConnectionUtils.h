#ifndef CONNECTIONUTILS_H
#define CONNECTIONUTILS_H
#include <vector>
namespace PortUtils {
int generate(int minPort = 1024,
             int maxPort = 65535,
             const std::vector<int>& excluded = {});
}

#endif // CONNECTIONUTILS_H
