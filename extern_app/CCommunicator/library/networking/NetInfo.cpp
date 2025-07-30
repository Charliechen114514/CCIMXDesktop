#include "NetInfo.h"

bool SelfInfo::isValud() const {
    return port > 0;
}

bool PeerInfo::isValid() const {
    return !host_address.isEmpty() && target_port > 0;
}
