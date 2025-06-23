#ifndef NETSTATUSCHANGEDEVENT_H
#define NETSTATUSCHANGEDEVENT_H

#include "../StatusBarIconWidget.h"
#include "builtin/core/netability_scanner/NetAbilityScanEnum.h"

/**
 * @brief Event representing network status changes.
 *
 * Carries information about network connectivity state changes.
 */
struct NetStatusChangedEvent : public IconEvent {
    /**
     * @brief Constructs a network status change event.
     * @param netIcon Associated network icon widget
     * @param parent Parent object (optional)
     */
    explicit NetStatusChangedEvent(StatusBarIconWidget* netIcon, QObject* parent)
        : IconEvent(netIcon, parent) {
    }

    NetWorkState status { NetWorkState::DISCONNECTED };  ///< Current network state
};

#endif // NETSTATUSCHANGEDEVENT_H