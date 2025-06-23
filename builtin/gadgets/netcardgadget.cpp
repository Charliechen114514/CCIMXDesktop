#include "netcardgadget.h"
#include "desktoptoast.h"

NetCardGadget::
    NetCardGadget(DesktopToast* toast, QWidget* parent)
    : AppCardWidget(toast, parent) {
    /* actually do nothing in the init status */
    setCurrentIcon(QPixmap(":/icons/wait_connecting.png"));
}

/* apps are about to invoke his work */
void NetCardGadget::invoke_preLaunch_work() {
    // do nothing here
}

void NetCardGadget::postAppCardWidget() {
	const char* msg;
	switch (cache_reachability) {
	case NetWorkState::DISCONNECTED:
		msg = "Machine Now is Disconnected! Check the network settings!";
		break;
	case NetWorkState::LOCAL:
		/* machine is only available to visit local or in sites*/
		msg = "Machine Now is Only available in Ethernet!";
		break;
	case NetWorkState::ONLINE:
		/* machine is online */
		msg = "Machine Now is available to access Internet!";
		break;
	default:
		msg = "Machine is seemingly connecting to the network...";
		break;
	}

	binding_toast->set_message(msg);
}

void NetCardGadget::process_once_fresh(NetWorkState status) {
    cache_reachability = status;
	/* monitoring handlings */
	switch (cache_reachability) {
	case NetWorkState::DISCONNECTED:
		setCurrentIcon(QPixmap(":/icons/disconnected_wifi.png"));
		break;
	case NetWorkState::LOCAL:
		setCurrentIcon(QPixmap(":/icons/local_only.png"));
		break;
	case NetWorkState::ONLINE:
		/* machine is online */
		setCurrentIcon(QPixmap(":/icons/connected_wifi.png"));
		break;
	default:
		setCurrentIcon(QPixmap(":/icons/wait_connecting.png"));
		break;
	}
}
