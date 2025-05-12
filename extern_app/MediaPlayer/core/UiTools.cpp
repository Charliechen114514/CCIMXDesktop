#include "UiTools.h"
#include <QFileInfo>
#include <QTime>

/* Typically, we assigned with Hour : Mins : Seconds */
QString UiTools::toMediaTypicalTimeStr(const qint64 time) {
	return QTime::fromMSecsSinceStartOfDay(time).toString(TYPICAL_FORMAT);
}

/* from msecs to secs */
std::pair<qint64, qint64> UiTools::downcast_to_sliderable_period(qint64 min, qint64 max) {
	return { min / 1000, max / 1000 };
}

QString UiTools::toScrollLabelText(const QString& src_path) {
	return QString("Current Playing: ") + QFileInfo(src_path).fileName();
}
