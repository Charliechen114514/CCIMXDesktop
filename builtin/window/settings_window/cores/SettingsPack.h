#ifndef SETTINGSPACK_H
#define SETTINGSPACK_H
#include <QFont>
#include <QColor>
/**
 * @brief The InfoPack class helps to
 * figure out the settings
 */
struct AppWidgetsSettingsInfoPack {
    QColor fontColor;
    QFont font;
    int iconSize;
};

#endif // SETTINGSPACK_H
