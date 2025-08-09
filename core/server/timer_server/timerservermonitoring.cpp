#include "timerservermonitoring.h"
#include "timerhandleserver.h"
#include "core/loggers/DesktopLoggerConvinients.h"
#include <QDebug>
TimerServerMonitoring::TimerServerMonitoring(QObject* parent)
    : DesktopServerBase { parent } {
}

TimerServerMonitoring::~TimerServerMonitoring()
{
    qDebug() << "Releasing the TimerServerMonitoring";
    QStringList ids;
    for(const auto& each : timerServer){
        ids << each->id();
    }
    for(const auto& id : ids){
        remove_server_id(id);
    }
}

void TimerServerMonitoring::attach_server(TimerHandleServer *raw_server)
{
    if(!raw_server){
        Logger::postError(name,
                          "Empty Server attached is not permitted!");
        return;
    }

    auto iterator = timerServer.find(raw_server->id());
    if(iterator != timerServer.end()){
        // This is the duplicate session
        Logger::postError(name, "Duplicate Server attach request: " + raw_server->server_name());
        return;
    }
    raw_server->setParent(this);
    timerServer.insert(raw_server->id(), raw_server);
    Logger::postInfo(name, "Server Insert OK: " + raw_server->server_name());
}

TimerHandleServer* TimerServerMonitoring::install_server(
    const unsigned int runs_interval,
    QString &&name,
    ServerRunner&&functor)
{
    TimerHandleServer* server = new TimerHandleServer(
        name, functor, runs_interval, this);
    server->setParent(this);
    timerServer.insert(server->id(), server);
    Logger::postInfo(name, "Server Install OK: " + name);
    return server;
}

void TimerServerMonitoring::remove_server_name(const QString &name)
{
    auto it = timerServer.begin();

    while(it != timerServer.end()){
        if(it.value()->server_name() == name){
            Logger::postDebug(this->name,
                              "Find target name: " +
                                  name +
                                  " with server id:" +
                                  it.value()->id());
            auto server = it.value();
            it = timerServer.erase(it);
            server->setState(false);
            server->deleteLater();
        }else{
            ++it;
        }
    }
}

void TimerServerMonitoring::remove_server_id(const ServerID &id)
{
    auto iterator = timerServer.find(id);
    if(iterator == timerServer.end()){
        // This is the duplicate session
        Logger::postError(name, "We dont find a server request "
                                "from remove_server_id in TimerServerMonitoring"
                                " which, the id is: " + id);
        return;
    }

    auto server_handle = iterator.value();
    timerServer.remove(id);
    server_handle->setState(false);
    server_handle->deleteLater();
}

TimerHandleServer* TimerServerMonitoring::query_from_id(const ServerID& id)
{
    return timerServer.value(id);
}

void TimerServerMonitoring::setServerState(
    const ServerID &id, bool st)
{
    auto iterator = timerServer.find(id);
    if(iterator == timerServer.end()){
        // This is the duplicate session
        Logger::postError(name, "We dont find a server request "
                                "from remove_server_id in TimerServerMonitoring"
                                " which, the id is: " + id);
        return;
    }

    auto server_handle = iterator.value();
    server_handle->setState(st);
}

void TimerServerMonitoring::run_connection_setup(TimerHandleServer *s)
{
    connect(s, &TimerHandleServer::server_finished,
            this, [this, s](){
                emit  server_finished(s->id());
            });
    connect(s, &TimerHandleServer::server_shutdown,
            this, [this, s](){
                emit server_destoryed(s->id());
            });
    connect(s, &TimerHandleServer::server_status_changed,
            this, [this, s](bool st){
                if(st){
                    emit server_depatched_run(s->id());
                }else{
                    emit server_hanged(s->id());
                }
            });
    connect(s, &TimerHandleServer::timer_alert,
            this, [this, s](){
                emit server_activate_once(s->id());
            });
}
