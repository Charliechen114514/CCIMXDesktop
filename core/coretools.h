#ifndef CORETOOLS_H
#define CORETOOLS_H
#include <QStringList>

namespace CoreTools
{

QStringList     enumeratefiles(const QString& path, const QStringList& nameFilters);

float           random_float(const float min, const float max);





}

#endif // CORETOOLS_H
