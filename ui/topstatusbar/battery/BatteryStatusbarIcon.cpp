#include "BatteryStatusbarIcon.h"
#include "DefaultLabelName.h"
BatteryStatusbarIcon::BatteryStatusbarIcon(QWidget* widget)
    : StaticStatusBarIconWidget(TopStatusBar_LabelName::BATTERY, widget) {
    setIcon(QPixmap(":/netstat/icons/battery_charging.png"));
}
