#ifndef QTADAPTTOOLS_H
#define QTADAPTTOOLS_H
#include <QImage>
class CVImage;

/**
 * @brief The QtAdaptTools namespace provides the tools
 * @note Most of the implementations, for management
 * reason, are supposed to place in the impl
 * files, instead of the current cpp file
 */
namespace QtAdaptTools {

/**
 * @brief toQImage convert the CVImage to QImage
 * @param cvImage the CVImage to convert
 * @return the QImage
 */
QImage toQImage(const CVImage& cvImage);

QImage toDisplayableImage(const CVImage& cvImage);

}

#endif // QTADAPTTOOLS_H
