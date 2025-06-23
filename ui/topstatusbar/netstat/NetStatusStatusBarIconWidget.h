#ifndef NETSTATUSSTATUSBARICONWIDGET_H
#define NETSTATUSSTATUSBARICONWIDGET_H

#include "../StaticStatusBarIconWidget.h"
#include "builtin/core/netability_scanner/NetAbilityScanEnum.h"
#include <QWidget>

namespace Ui {
class NetStatusStatusBarIconWidget;
}

/**
 * @brief Network status indicator widget for status bar.
 *
 * Shows current network connectivity status and handles related events.
 */
class NetStatusStatusBarIconWidget : public StaticStatusBarIconWidget {
    Q_OBJECT

public:
    /**
     * @brief Constructs the network status widget.
     * @param parent Parent widget (optional)
     */
    explicit NetStatusStatusBarIconWidget(QWidget* parent = nullptr);
    
    /**
     * @brief Updates the displayed network status.
     * @param type New network state to display
     */
    void processingStatus(NetWorkState type);
    
    /**
     * @brief Handles icon-related events.
     * @param icons Event to process
     * @return true if event was handled, false otherwise
     */
    bool iconEvents(IconEvent* icons) override;
};

#endif // NETSTATUSSTATUSBARICONWIDGET_H