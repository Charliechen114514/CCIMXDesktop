#ifndef DEFAULTLABELNAME_H
#define DEFAULTLABELNAME_H

/**
 * @file defaultlabelname.h
 * @brief Defines default label names used in the top status bar.
 */

/**
 * @namespace TopStatusBar_LabelName
 * @brief Contains constant label names for different status bar widgets.
 */
namespace TopStatusBar_LabelName {

/**
 * @brief Label name for the network status icon.
 */
static constexpr const char* NETSTAT = "netstate";

/**
 * @brief Label name for the time display.
 */
static constexpr const char* TIME = "time_display";

/**
 * @brief Label name for the battery indicator.
 */
static constexpr const char* BATTERY = "battery";

}; // namespace TopStatusBar_LabelName

#endif // DEFAULTLABELNAME_H
