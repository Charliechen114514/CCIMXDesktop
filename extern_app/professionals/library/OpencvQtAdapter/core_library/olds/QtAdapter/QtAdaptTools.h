#ifndef QTADAPTTOOLS_H
#define QTADAPTTOOLS_H
#include <QImage>
class CVImage;
namespace QtAdaptTools {
/* toQImage */
QImage toQImage(const CVImage& cvImage);
}

#endif // QTADAPTTOOLS_H
