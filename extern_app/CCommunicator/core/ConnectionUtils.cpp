#include "ConnectionUtils.h"
#include <random>
#include <set>

int PortUtils::generate(int minPort,
                        int maxPort,
                        const std::vector<int>& excluded) {
    static std::mt19937 gen { std::random_device {}() };
    std::uniform_int_distribution<> dist(minPort, maxPort);
    std::set<int> exset(excluded.begin(), excluded.end());

    int p;
    do {
        p = dist(gen);
    } while (exset.count(p) > 0);
    return p;
}
