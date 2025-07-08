#include "netcardgadget.h"
#include "desktoptoast.h"
#include <QGraphicsDropShadowEffect>
#include <QLabel>
NetCardGadget::
    NetCardGadget(DesktopToast* toast, QWidget* parent)
    : AppCardWidget(toast, parent) {
    /* actually do nothing in the init status */
    setCurrentIcon(QPixmap(":/icons/wait_connecting.png"));

    setObjectName("NetworkStatusCard");
    setAttribute(Qt::WA_StyledBackground);
    setAutoFillBackground(true);

    setObjectName("AppCardWidget");
    setStyleSheet(R"(
    #AppCardWidget {
    border-radius: 20px;
    background: qlineargradient(
        x1: 0, y1: 0, x2: 0, y2: 1,
        stop: 0 #00B894,
        stop: 1 #00695C
    );
    padding: 12px;
    }
)");
    auto* shadow = new QGraphicsDropShadowEffect(this);
    shadow->setBlurRadius(10);
    shadow->setOffset(0, 4);
    shadow->setColor(QColor(0, 0, 0, 160));
    setGraphicsEffect(shadow);
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

void NetCardGadget::setupSelfTextLabelStyle(QLabel* selfTextLabel) {
    selfTextLabel->setAlignment(Qt::AlignCenter);
    selfTextLabel->setStyleSheet(R"(
    QLabel {
        color: white;
        font-size: 12px;
        font-weight: bold;
    }
)");
}

void NetCardGadget::process_once_fresh(NetWorkState status) {
    cache_reachability = status;
    operate_comment_label();
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
    operate_comment_label();
}

void NetCardGadget::operate_comment_label() {
    const char* msg;
    switch (cache_reachability) {
    case NetWorkState::DISCONNECTED:
        msg = "Disconnected";
        break;
    case NetWorkState::LOCAL:
        /* machine is only available to visit local or in sites*/
        msg = "Ethernet";
        break;
    case NetWorkState::ONLINE:
        /* machine is online */
        msg = "Internet";
        break;
    default:
        msg = "Loading...";
        break;
    }

    setHelperFunction(msg);
}
