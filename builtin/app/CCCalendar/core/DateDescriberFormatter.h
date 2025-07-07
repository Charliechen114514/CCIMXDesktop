#ifndef DATEDESCRIBERFORMATTER_H
#define DATEDESCRIBERFORMATTER_H

#include <QString>
class QDate;

/**
 * @namespace DateDescriberFormatter
 */
namespace DateDescriberFormatter {

/**
 * @brief describeDate fetch the string
 * @param date date wait describe
 * @return strings
 */
QString describeDate(const QDate& date);

};

#endif // DATEDESCRIBERFORMATTER_H
