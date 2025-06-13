#ifndef WALLPAPERUTILSCOLLIECTIONS_H
#define WALLPAPERUTILSCOLLIECTIONS_H
#include <QStringList>
/**
 * @namespace WallPaperUtilsColliections
 * @brief handle the utils collections of WallPaper relative
 */
namespace WallPaperUtilsColliections {
/**
 * @brief collect_from_qrcs collect from qrc files
 * @return
 */
QStringList collect_from_qrcs();

/**
 * @brief prefix for searchings
 *
 */
static constexpr const char* PREFIX[] = { "*.png" };

/**
 * @brief prefixs get to StringList
 * @return
 */
QStringList prefixs();

};

#endif // WALLPAPERUTILSCOLLIECTIONS_H
