#ifndef UITOOLS_H
#define UITOOLS_H
#include <QString>
namespace UiTools {

static constexpr const char* TYPICAL_FORMAT = "HH:mm:ss";

QString toMediaTypicalTimeStr(const qint64 time);

/* downcast to seconds level for slider */
std::pair<qint64, qint64> downcast_to_sliderable_period(qint64 min, qint64 max);

/* downcast to seconds for position issue */
inline qint64 downcast_to_sliderable_position(qint64 position) {
	return position / 1000;
}

inline qint64 upcast_to_mseconds(qint64 position) {
	return position * 1000;
}

QString toScrollLabelText(const QString& src_path);

};

#endif // UITOOLS_H
