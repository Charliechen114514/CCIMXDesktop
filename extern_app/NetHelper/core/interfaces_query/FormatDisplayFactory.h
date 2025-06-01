#ifndef FORMATDISPLAYFACTORY_H
#define FORMATDISPLAYFACTORY_H
#include <QString>
class QNetworkInterface;
namespace FormatDisplayFactory {
using Property = QString; ///< property string
using Value = QString; ///< value string

/**
 * @brief details format to displayable strings
 * @param interfaces what netcard?
 * @return result
 */
QList<QPair<Property, Value>> details(const QNetworkInterface& interfaces);
};

#endif // FORMATDISPLAYFACTORY_H
