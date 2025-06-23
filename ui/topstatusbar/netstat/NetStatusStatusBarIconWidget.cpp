#include "NetStatusStatusBarIconWidget.h"
#include "../DefaultLabelName.h"
#include "NetStatusChangedEvent.h"
NetStatusStatusBarIconWidget::NetStatusStatusBarIconWidget(QWidget* parent)
    : StaticStatusBarIconWidget(TopStatusBar_LabelName::NETSTAT, parent) {
    processingStatus(NetWorkState::UNKNOWN);
}

void NetStatusStatusBarIconWidget::processingStatus(NetWorkState type) {
    QString src_path;
    switch (type) {
    case NetWorkState::DISCONNECTED:
        src_path = ":/netstat/icons/disconnected_wifi.png";
        break;
    case NetWorkState::LOCAL:
        src_path = ":/netstat/icons/local_only.png";
        break;
    case NetWorkState::ONLINE:
        src_path = ":/netstat/icons/connected_wifi.png";
        break;
    case NetWorkState::UNKNOWN:
        src_path = ":/netstat/icons/wait_connecting.png";
        break;
    }
    this->setIcon(QPixmap(src_path));
}

bool NetStatusStatusBarIconWidget::iconEvents(IconEvent* icons) {
    NetStatusChangedEvent* event = dynamic_cast<NetStatusChangedEvent*>(icons);
    if (!event) {
        // throw to the father implements
        return StaticStatusBarIconWidget::iconEvents(icons); // missing types
    }

    processingStatus(event->status);
    return true;
}
