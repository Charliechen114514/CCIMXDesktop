#ifndef DESKTOP_SETTINGS_H
#define DESKTOP_SETTINGS_H

#ifdef _WIN32 // Windows Build

/**
 * @brief the default desktop places
 */
#define DEFAULT_DESKTOP_PLACES "D:/EnlistsImages/"

#else

#ifdef ARM_BUILD /* Is this special for ARM Build ? */

#define DEFAULT_DESKTOP_PLACES "/home/charliechen/Pictures/"

#else

/* Or we see in the Ubuntu24.04 */
#define DEFAULT_DESKTOP_PLACES "/home/charliechen/Pictures/"

#endif

#endif

#endif // DESKTOP_SETTINGS_H
