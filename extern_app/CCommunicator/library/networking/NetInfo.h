#ifndef NETINFO_H
#define NETINFO_H
#include <QString>
struct SelfInfo {
    ~SelfInfo() = default;
    int port;
    bool isValud() const;
};

struct PeerInfo {
    ~PeerInfo() = default;
    QString host_address;
    int target_port;
    bool isValid() const;
};

#endif // NETINFO_H
