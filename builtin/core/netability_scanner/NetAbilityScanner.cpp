#include "NetAbilityScanner.h"
#include <QHostAddress>
#include <QNetworkAccessManager>
#include <QNetworkInterface>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QTimer>
NetAbilityScanner::NetAbilityScanner(QObject* parent)
    : QObject { parent } {
    scan_timer = new QTimer(this);
    scan_timer->setInterval(3000);
    connect(scan_timer, &QTimer::timeout, this, &NetAbilityScanner::process_once_fresh);
    scan_timer->start();
}

void NetAbilityScanner::process_once_fresh() {
    process_once_online_check();
}

void NetAbilityScanner::process_once_local_check() {
    const QList<QNetworkInterface> interfaces = QNetworkInterface::allInterfaces();
    for (const QNetworkInterface& interface : interfaces) {
        if (interface.flags().testFlag(QNetworkInterface::IsUp) && interface.flags().testFlag(QNetworkInterface::IsRunning) && !interface.flags().testFlag(QNetworkInterface::IsLoopBack)) {

            for (const QNetworkAddressEntry& entry : interface.addressEntries()) {
                QHostAddress ip = entry.ip();
                if (ip.protocol() == QAbstractSocket::IPv4Protocol) {
                    emit postStatus(NetWorkState::LOCAL);
                    return;
                }
            }
        }
    }
    emit postStatus(NetWorkState::DISCONNECTED);
}

void NetAbilityScanner::process_once_online_check() {
    if (!manager)
        manager = new QNetworkAccessManager(this);
    QNetworkRequest request = QNetworkRequest(QUrl(online_base_work));

    QNetworkReply* reply = manager->head(request);
    QTimer::singleShot(3000, reply, &QNetworkReply::abort); // 超时3秒

    connect(reply, &QNetworkReply::finished, [this, reply]() {
        if (reply->error() == QNetworkReply::NoError) {
            emit postStatus(NetWorkState::ONLINE);
        } else {
            process_once_local_check();
        }
        reply->deleteLater();
    });
}
