#include "screendetectorserver.h"
#include "builtin/core/backlight/BackLightControllerSingleton.h"
#include "builtin/core/backlight/BacklightController.h"
#include "core/server/timer_server/timerhandleserver.h"
#include "core/loggers/DesktopLoggerConvinients.h"
#include "core/server/timer_server/timerservermonitoring.h"
#include <QDebug>
ScreenDetectorServer::ScreenDetectorServer(TimerServerMonitoring* object) : QObject(object){
    if(!object) throw std::invalid_argument("NULL Timer server makes no sense!");
    handling_server = object;
    run_registering();
}

ScreenDetectorServer::~ScreenDetectorServer()
{
    qDebug() << "Remove the ScreenDetectorServer";
}

void ScreenDetectorServer::set_shutoff_interval(
    const int interval, const bool request_imm)
{
    this->shutoff_interval = interval;
    auto server_type = handling_server->query_from_id(cached_id);
    if(server_type){
        server_type->adjust_timer_interval(interval, request_imm);
    }else{
        qCritical()	<< "Failed Due to unfind server handle";
    }
}

void ScreenDetectorServer::process_reset_timer()
{
    auto server_type = handling_server->query_from_id(cached_id);
    if(server_type){
        server_type->restart_timer();
        run_set_light_level(old_level);
        Logger::postInfo(server_name, "OK, we resume the light level as old: " + QString::number(old_level));
    }else{
        qCritical()	<< "Failed Due to unfind server handle";
    }
}

void ScreenDetectorServer::run_registering()
{
    // OK, running these register
    if(cached_id.isEmpty()){
        // OK, we must make a new registering
        TimerHandleServer* server = new TimerHandleServer(
            server_name,
            std::bind(&ScreenDetectorServer::__internal_checker,
                      this),
            shutoff_interval,handling_server);
        handling_server->attach_server(server);
        cached_id = server->id();
        Logger::postInfo(server_name, "OK, we get the id: " + cached_id + ", And we shell open the cases!");
        server->setState(true);
    }else{
        qCritical() << "Error in run registering, server is already in!";
    }
}

void ScreenDetectorServer::run_set_light_level(const int level)
{
    auto light_instance = BackLightControllerSingleton::instance();
    old_level = light_instance->lightLevel();
    light_instance->setLightLevel(level);
}

bool ScreenDetectorServer::__internal_checker()
{
    const int level = 0;
    run_set_light_level(level);
    Logger::postInfo("Set the light with level: "
                     + QString::number(level));
    return true; // server shell never failed!
}
