#ifndef TIMESERVERTYPE_H
#define TIMESERVERTYPE_H
#include <functional>
#include <QString>
using ServerID = QString;

/**
 * ServerRunner requires the function handle
 * to return server status
 */
using ServerRunner = std::function<bool(void)>;

struct TimerServerProperty {
    bool isSelfDestoryed;
    bool isSingleShot;
    bool isRunning;
    QString server_name;
    ServerID id;
};

#endif // TIMESERVERTYPE_H
