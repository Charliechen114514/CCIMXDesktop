#ifndef SCREENDETECTORSERVER_H
#define SCREENDETECTORSERVER_H
#include <QObject>
#include "core/server/timer_server/TimeServerType.h"
class TimerHandleServer;
class TimerServerMonitoring;

class ScreenDetectorServer : public QObject {
    Q_OBJECT
public:
    explicit ScreenDetectorServer(TimerServerMonitoring* object);
    ~ScreenDetectorServer();
    inline int get_shutoff_interval() const noexcept {return shutoff_interval;}
    void set_shutoff_interval(const int interval, const bool request_imm = true);

public slots:
    void process_reset_timer();

private:
    void run_registering();
    void run_set_light_level(const int level);
    bool __internal_checker();
    int shutoff_interval{ 5000 };
    const QString server_name {"BackLight Auto Controller"};
    QString cached_id{};
    ServerRunner screen_detector;
    TimerServerMonitoring* handling_server;
    int old_level {0};
};

#endif // SCREENDETECTORSERVER_H
