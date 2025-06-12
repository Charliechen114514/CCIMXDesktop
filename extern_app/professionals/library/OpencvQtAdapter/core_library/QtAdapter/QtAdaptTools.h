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

/**
 * @brief toDisplayableImage converts to the direct displayable
 * 
 * @param cvImage the CVImage to convert
 * @return QImage 
 */
QImage toDisplayableImage(const CVImage& cvImage);

/**
 * @brief fromRGBQImage trans image from QImage to CVImage
 * 
 * @param image 
 * @return CVImage 
 */
CVImage fromRGBQImage(const QImage& image);

}

#endif // QTADAPTTOOLS_H
