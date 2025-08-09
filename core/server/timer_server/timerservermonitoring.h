#ifndef TIMERSERVERMONITORING_H
#define TIMERSERVERMONITORING_H
#include <QMap>
#include <QString>
#include <QObject>
#include "TimeServerType.h"
#include "core/server/DesktopServerBase.h"
class TimerHandleServer;

class TimerServerMonitoring : public DesktopServerBase {
	Q_OBJECT
public:
    explicit TimerServerMonitoring(QObject* parent = nullptr);
    ~TimerServerMonitoring();
    /**
     * @brief attach_server
     * @param raw_server raw server created other way
     * @warning this shell be force reset parent and let
     * TimerServerMonitoring monitor the parent session
     */
    void attach_server(TimerHandleServer* raw_server);

    /**
     * @brief install_server install the server directly
     * @param runs_interval
     * @param name
     * @param functor
     * @return returns the handle
     */
    TimerHandleServer *install_server(const unsigned int runs_interval,
                        QString&& name,
                        ServerRunner &&functor);

    /**
     * @brief remove_server_name
     * remove all the server with target name given
     * @param name
     */
    void remove_server_name(const QString& name);

    /**
     * @brief remove_server_id session id
     * @param id removed server session id
     */
    void remove_server_id(const ServerID& id);

    /**
     * @brief query_from_id query the server handle
     * @param id id we ready check
     * @return
     */
    TimerHandleServer* query_from_id(const ServerID& id);

    void setServerState(const ServerID &id, bool st);

signals:
    void server_activate_once(const ServerID& id);
    void server_finished(const ServerID& id);
    void server_hanged(const ServerID& id);
    void server_depatched_run(const ServerID& id);
    void server_destoryed(const ServerID& id);

private:
    QMap<ServerID, TimerHandleServer*> timerServer;
    const QString name {"Timer Monitoring Server"};

private:
    void run_connection_setup(TimerHandleServer* s);
};

#endif // TIMERSERVERMONITORING_H
