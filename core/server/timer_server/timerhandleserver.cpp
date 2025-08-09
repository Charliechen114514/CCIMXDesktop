#include "timerhandleserver.h"
#include "core/loggers/DesktopLoggerConvinients.h"
#include <QUuid>
#include <QDebug>

TimerHandleServer::TimerHandleServer(
    const QString &name,
    const ServerRunner &runner,
    const int timer_interval, QObject *parent):
    QObject { parent },
    timer_server_id(QUuid::createUuid().toString()),
    runner(runner),
    name(name),
    runny_timer(this)
{
    runny_timer.setInterval(timer_interval);
    connect(&runny_timer, &QTimer::timeout,
            this, &TimerHandleServer::run_raw_hook);
}

TimerHandleServer::TimerHandleServer(
    QString &&name, ServerRunner &&runner,
    const int timer_interval, QObject *parent):
    QObject { parent },
    timer_server_id(QUuid::createUuid().toString()),
    name(std::move(name)),
    runner(std::move(runner)),
    runny_timer(this)
{
    runny_timer.setInterval(timer_interval);
    connect(&runny_timer, &QTimer::timeout,
            this, &TimerHandleServer::run_raw_hook);
}

TimerHandleServer::~TimerHandleServer()
{
    Logger::postDebug(name, "is cleaning self...");
    if(runny_timer.isActive()){
        runny_timer.stop();
        emit server_shutdown();
    }
}

void TimerHandleServer::setAsRunOnce(bool ifSelfDeleted)
{
    runny_timer.setSingleShot(true);
    if(ifSelfDeleted){
        connect(this, &TimerHandleServer::server_ready_destroyed,
                this, &TimerHandleServer::deleteLater);
    }else{
        disconnect(this, &TimerHandleServer::server_ready_destroyed,
                    this, &TimerHandleServer::deleteLater);
    }
}

void TimerHandleServer::resetServer()
{
    runny_timer.setSingleShot(false);
    disconnect(this, &TimerHandleServer::server_ready_destroyed,
               this, &TimerHandleServer::deleteLater);
    isSelfDeleted = false;
}

const TimerServerProperty TimerHandleServer::serverProperty() const noexcept
{
    return {
        isSelfDeleted,
        runny_timer.isSingleShot(),
        runny_timer.isActive(),
        name,
        timer_server_id
    };
}

void TimerHandleServer::setState(bool should_run)
{
    if(should_run){
        runny_timer.start();
        emit server_status_changed(true);
    }else{
        runny_timer.stop();
        emit server_status_changed(false);
        run_cleanup();
    }
}

void TimerHandleServer::adjust_timer_interval(const int new_interval, bool request_immediate)
{
    if(request_immediate){
        runny_timer.stop();
    }
    runny_timer.setInterval(new_interval);
    Logger::postInfo(name, "New Timer Interval's here: " + QString::number(new_interval));
    if(request_immediate){
        runny_timer.start();
    }
}

void TimerHandleServer::quit_self()
{
    setAsRunOnce(true);
    setState(false);
}

void TimerHandleServer::restart_timer()
{
    if(runny_timer.isActive()){
        Logger::postDebug(name, "Server is invoked as restart timer shots");
        runny_timer.start();
    }else{
        Logger::postWarning(name, "Server is not running, calling this makes nosense!");
    }
}

void TimerHandleServer::run_raw_hook()
{
    // emit the run server ready first
    emit timer_alert();

    if(!runner){
        Logger::postWarning(name, "The Timer Server is Ready but the"
                                  " Runner is Empty!");
        return;
    }

    Logger::postDebug(name, "Timer Alert, Run the session");
    bool result = runner();
    Logger::postDebug(name, "Running Session Finished! Check the session");
    if(result){
        Logger::postInfo(name, "Runner success");
    }else{
        Logger::postWarning(name, "Runner failed!");
    }

    emit server_finished();
    if(runny_timer.isSingleShot()){
        setState(false);
    }
}

void TimerHandleServer::run_cleanup()
{
    Logger::postDebug(name, "This Server shell be terminated!");
    if(isSelfDeleted){
        emit server_ready_destroyed();
    }
}









