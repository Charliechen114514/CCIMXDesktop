#include "UiTools.h"
#include <QTime>

/* Typically, we assigned with Hour : Mins : Seconds */
QString UiTools::toMediaTypicalTimeStr(const qint64 time) {
	return QTime::fromMSecsSinceStartOfDay(time).toString(TYPICAL_FORMAT);
}

/* from msecs to secs */
std::pair<qint64, qint64> UiTools::downcast_to_sliderable_period(qint64 min, qint64 max) {
	return { min / 1000, max / 1000 };
}
