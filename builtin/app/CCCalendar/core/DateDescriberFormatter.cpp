#include "DateDescriberFormatter.h"
#include <QDate>
QString DateDescriberFormatter::describeDate(const QDate& date) {
    if (!date.isValid()) {
        return QStringLiteral("🚫 Invalid date provided.");
    }
    // Construct description
    QString desc;
    desc += "📅 Detailed Date Description:\n";
    desc += QString("• Year              : %1\n").arg(date.year());
    desc += QString("• Month             : %1 (%2)\n").arg(date.month()).arg(date.toString("MM"));
    desc += QString("• Day               : %1\n").arg(date.day());
    desc += QString("• Weekday           : %1 (%2)\n").arg(date.toString("ddd"), date.toString("dddd"));
    desc += QString("• Day of year       : %1\n").arg(date.dayOfYear());
    desc += QString("• Leap year?        : %1\n").arg(date.isLeapYear(date.year()) ? "Yes" : "No");
    desc += QString("• Days in month     : %1\n").arg(date.daysInMonth());
    desc += QString("• Days in year      : %1\n").arg(date.daysInYear());
    return desc;
}
