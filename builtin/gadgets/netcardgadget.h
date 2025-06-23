#ifndef NETCARDGADGET_H
#define NETCARDGADGET_H
#include "appcardwidget.h"
#include "builtin/core/netability_scanner/NetAbilityScanEnum.h"

/**
 * @brief The NetCardGadget class is a netcards to test if the
 * machine is connecting to the internet
 */
class NetCardGadget : public AppCardWidget {
public:
	NetCardGadget() = delete;
	/**
	 * @brief disable copy
     *
	 */
	Q_DISABLE_COPY(NetCardGadget);
	/**
	 * @brief Construct a new Net Card Gadget object
     *
     * @param toast
     * @param parent
	 */
	explicit NetCardGadget(DesktopToast* toast, QWidget* parent);
	/**
	 * @brief invoke_preLaunch_work is the main function to invoke the prelaunching issue
	 * @note when system starts, app cards are supposed to do their actions
	 * and if not, then do nothing
	 */
	void invoke_preLaunch_work() override;
    /**
     * @brief process_once_fresh flush the status for once
     * @param status
     */
    void process_once_fresh(NetWorkState status);

protected:
	/**
	 * @brief postAppCardWidget, sometimes, we can use this to post the
	 * messages to the binding_toast
	 */
	void postAppCardWidget() override;

private:
    NetWorkState cache_reachability;
};

#endif // NETCARDGADGET_H
