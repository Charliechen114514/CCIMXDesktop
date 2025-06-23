#ifndef NETSTATUSCHANGEDEVENT_H
#define NETSTATUSCHANGEDEVENT_H
#include "../StatusBarIconWidget.h"
#include "builtin/core/netability_scanner/NetAbilityScanEnum.h"
struct NetStatusChangedEvent : public IconEvent {
    explicit NetStatusChangedEvent(StatusBarIconWidget* netIcon, QObject* parent)
        : IconEvent(netIcon, parent) {
    }

    NetWorkState status { NetWorkState::DISCONNECTED };
};

#endif // NETSTATUSCHANGEDEVENT_H
