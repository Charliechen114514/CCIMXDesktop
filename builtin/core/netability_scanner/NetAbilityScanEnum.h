#ifndef NETABILITYSCANENUM_H
#define NETABILITYSCANENUM_H
/**
 * @brief The NetWorkState enum enumerate the network state
 */
enum class NetWorkState {
    UNKNOWN, ///< Unknown state, impossible for... current now?
    DISCONNECTED, ///< Machine is disconnected, nether locally nor internetly
    LOCAL, ///< Machine is only available to local network, but is limited to access the internet
    ONLINE ///< Machine is online, available to access the internet
};

#endif // NETABILITYSCANENUM_H
