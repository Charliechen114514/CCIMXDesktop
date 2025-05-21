#ifndef NETCARDGADGET_H
#define NETCARDGADGET_H
#include "appcardwidget.h"

/**
 * @brief The NetCardGadget class is a netcards to test if the
 * machine is connecting to the internet
 */
class NetCardGadget : public AppCardWidget {
public:
	/**
	 * @brief The NetWorkState enum enumerate the network state
	 */
	enum class NetWorkState {
		UNKNOWN, ///< Unknown state, impossible for... current now?
		DISCONNECTED, ///< Machine is disconnected, nether locally nor internetly
		LOCAL, ///< Machine is only available to local network, but is limited to access the internet
		ONLINE ///< Machine is online, available to access the internet
	};

	NetCardGadget() = delete;
	Q_DISABLE_COPY(NetCardGadget);
	explicit NetCardGadget(DesktopToast* toast, QWidget* parent);
	/**
	 * @brief invoke_preLaunch_work is the main function to invoke the prelaunching issue
	 * @note when system starts, app cards are supposed to do their actions
	 * and if not, then do nothing
	 */
	void invoke_preLaunch_work() override;

protected:
	/**
	 * @brief postAppCardWidget, sometimes, we can use this to post the
	 * messages to the binding_toast
	 */
	void postAppCardWidget() override;

private:
	NetWorkState cache_reachability { NetWorkState::UNKNOWN };

	/* Followings are the checks of the network implementations */

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
};

#endif // NETCARDGADGET_H
