#ifndef BATTERYSTATUSBARICON_H
#define BATTERYSTATUSBARICON_H

#include "../StaticStatusBarIconWidget.h"

/**
 * @brief icons for batteries
 * 
 */
class BatteryStatusbarIcon : public StaticStatusBarIconWidget {
public:
    /**
     * @brief Construct a new Battery Statusbar Icon object
     * 
     * @param widget 
     */
    BatteryStatusbarIcon(QWidget* widget = nullptr);
};

#endif // BATTERYSTATUSBARICON_H
