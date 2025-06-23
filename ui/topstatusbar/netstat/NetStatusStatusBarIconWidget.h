#ifndef NETSTATUSSTATUSBARICONWIDGET_H
#define NETSTATUSSTATUSBARICONWIDGET_H
#include "../StaticStatusBarIconWidget.h"
#include "builtin/core/netability_scanner/NetAbilityScanEnum.h"
#include <QWidget>

namespace Ui {
class NetStatusStatusBarIconWidget;
}

class NetStatusStatusBarIconWidget : public StaticStatusBarIconWidget {
	Q_OBJECT
public:
    explicit NetStatusStatusBarIconWidget(QWidget* parent = nullptr);
    void processingStatus(NetWorkState type);
    bool iconEvents(IconEvent* icons) override;
};

#endif // NETSTATUSSTATUSBARICONWIDGET_H
