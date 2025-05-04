#ifndef NETCARDGADGET_H
#define NETCARDGADGET_H
#include "appcardwidget.h"

class NetCardGadget : public AppCardWidget
{
public:

    enum class NetWorkState{
        UNKNOWN,
        DISCONNECTED,
        LOCAL,
        ONLINE
    };

    NetCardGadget() = delete;
    Q_DISABLE_COPY(NetCardGadget);
    explicit NetCardGadget(DesktopToast* toast, QWidget* parent);
    void invoke_preLaunch_work() override;

protected:
    void postAppCardWidget() override;
private:
    NetWorkState                        cache_reachability{NetWorkState::UNKNOWN};
    void process_once_fresh();
    void process_once_local_check();
    void process_once_online_check();
    /* set the online check base net stations */
    static constexpr const char* online_base_work = "http://www.baidu.com";
    QTimer*     scan_timer;
};

#endif // NETCARDGADGET_H
