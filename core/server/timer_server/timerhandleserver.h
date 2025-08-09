#ifndef TIMERHANDLESERVER_H
#define TIMERHANDLESERVER_H
#include "TimeServerType.h"
#include <QObject>
#include <QTimer>
class TimerHandleServer : public QObject {
	Q_OBJECT
public:
    explicit TimerHandleServer(
        const QString& name,
        const ServerRunner& runner,
        const int timer_interval,
        QObject* parent = nullptr
        );
    explicit TimerHandleServer(QString&& name,
                               ServerRunner&& runner,
                               const int timer_interval,
                               QObject* parent = nullptr);

    Q_DISABLE_COPY(TimerHandleServer);
    ~TimerHandleServer();
    // self deleted will be set if given true
    /**
     * @brief setAsRunOnce set the timer handle sever
     * running once only
     * @param ifSelfDeleted: if true, after call the
     * server will destroy himself and dead
     */
    void setAsRunOnce(bool ifSelfDeleted = true);
    /**
     * @brief resetServer
     * reset the server to the plain type
     */
    void resetServer();
    const TimerServerProperty serverProperty() const noexcept;
    /**
     * @brief setState
     * @param should_run set the status of should we run session
     */
    void setState(bool should_run);

    /**
     * @brief adjust_timer_interval
     * @param new_interval
     * @param request_immediate request these or next session
     */
    void adjust_timer_interval(const int new_interval, bool request_immediate = true);

    void quit_self();

    /**
     * @brief restart_timer will reset the count of timer
     * to the cnt 0, which can be using in time resets
     */
    void restart_timer();

    inline const ServerID id() const noexcept{
        return timer_server_id;
    }

    inline const QString server_name() const noexcept {
        return name;
    }

signals:
    void server_status_changed(bool st);
    void timer_alert();
    void server_shutdown();
    void server_finished();
    void server_ready_destroyed();

private:
    const ServerID timer_server_id;
    QString name;
    ServerRunner runner;
    QTimer runny_timer;
    bool isSelfDeleted{false};

private:
    void run_raw_hook();
    void run_cleanup();
};

#endif // TIMERHANDLESERVER_H
