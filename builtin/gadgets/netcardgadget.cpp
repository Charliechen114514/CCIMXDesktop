#include "netcardgadget.h"
#include "desktoptoast.h"
#include <QHostAddress>
#include <QNetworkAccessManager>
#include <QNetworkInterface>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QTimer>
NetCardGadget::
    NetCardGadget(DesktopToast* toast, QWidget* parent)
    : AppCardWidget(toast, parent) {
    /* actually do nothing in the init status */
    setCurrentIcon(QPixmap(":/icons/wait_connecting.png"));
    scan_timer = new QTimer(this);
    scan_timer->setInterval(3000);
    connect(scan_timer, &QTimer::timeout, this, &NetCardGadget::process_once_fresh);
    scan_timer->start();
}

/* apps are about to invoke his work */
void NetCardGadget::invoke_preLaunch_work() {
	process_once_fresh();
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

void NetCardGadget::process_once_fresh() {
	process_once_online_check();
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

void NetCardGadget::process_once_local_check() {
	const QList<QNetworkInterface> interfaces = QNetworkInterface::allInterfaces();
	for (const QNetworkInterface& interface : interfaces) {
		if (interface.flags().testFlag(QNetworkInterface::IsUp) && interface.flags().testFlag(QNetworkInterface::IsRunning) && !interface.flags().testFlag(QNetworkInterface::IsLoopBack)) {

			for (const QNetworkAddressEntry& entry : interface.addressEntries()) {
				QHostAddress ip = entry.ip();
				if (ip.protocol() == QAbstractSocket::IPv4Protocol) {
					cache_reachability = NetWorkState::LOCAL;
					return;
				}
			}
		}
	}
	cache_reachability = NetWorkState::DISCONNECTED;
}

void NetCardGadget::process_once_online_check() {
	QNetworkAccessManager* manager = new QNetworkAccessManager();
	QNetworkRequest request = QNetworkRequest(QUrl(online_base_work));

	QNetworkReply* reply = manager->head(request);
	QTimer::singleShot(3000, reply, &QNetworkReply::abort); // 超时3秒

	connect(reply, &QNetworkReply::finished, [this, reply]() {
		if (reply->error() == QNetworkReply::NoError) {
			cache_reachability = NetWorkState::ONLINE;
		} else {
			cache_reachability = NetWorkState::UNKNOWN;
			process_once_local_check();
		}
		reply->deleteLater();
	});
}
