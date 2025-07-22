#ifndef NETABILITYSCANNER_H
#define NETABILITYSCANNER_H
#include "NetAbilityScanEnum.h"
#include <QObject>
class QTimer;
class QNetworkAccessManager;
/**
 * @brief   The NetAbilityScanner class
 *          check the desktop network status
 */
class NetAbilityScanner : public QObject {
	Q_OBJECT
public:
    /**
     * @brief NetAbilityScanner scan the abilities
     * @param parent
     */
    explicit NetAbilityScanner(QObject* parent = nullptr);
    /**
     * @brief process_once_fresh: invoke this to make a full check
     * @note: levarage process here:
     * process_once_fresh -> process_once_online_check()
     *							|-> if success connected to internet, stops
     *							|-> else do process_once_local_check
     *									|-> if success, then local network is access
     *									|-> else, disconnected
     */
    void process_once_fresh();
signals:
    /**
     * @brief postStatus connect the signals for
     * @param status
     */
    void postStatus(NetWorkState status);

private:
    /**
     * @brief process_once_local_check: check if the machine is available to local network
     * @note: this is a full scan of the machine ip tables, if we owns ip, we think we basically acceptable to a local networks
     */
    void process_once_local_check();
    /**
     * @brief process_once_online_check: check if the machine is available to access the internet
     * @note: online_base_work is the base net stations, we can use this to check if the machine is available to access the internet
     * @see online_base_work
     */
    void process_once_online_check();
    /**
     * @brief online_base_work is the base net stations, we can use this to check if the machine is available to access the internet
     * using in process_once_online_check
     * @see process_once_online_check
     * @note set the online check base net stations
     */
    static constexpr const char* online_base_work = "http://www.baidu.com";

    QTimer* scan_timer; ///< timer triggers the scan sessions
    QNetworkAccessManager* manager = nullptr;
};

#endif // NETABILITYSCANNER_H
