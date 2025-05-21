#ifndef UITOOLS_H
#define UITOOLS_H
#include <QString>
namespace UiTools {

/**
 * @brief TYPICAL_FORMAT is the typical format for time we shell
 * see in the slider
 */
static constexpr const char* TYPICAL_FORMAT = "HH:mm:ss";

/**
 * @brief toMediaTypicalTimeStr convert the time to typical
 * format
 * @param time the time to convert
 * @return the typical format string
 * @note the format we use is TYPICAL_FORMAT
 * @see TYPICAL_FORMAT for details
 */
QString toMediaTypicalTimeStr(const qint64 time);

/**
 * @brief downcast_to_sliderable_period
 * downcast the period to sliderable, this is seconds level
 * @param min the first places
 * @param max the final places
 * @return the pair of the period that can be direct install to
 * the QSilder
 */
std::pair<qint64, qint64> downcast_to_sliderable_period(qint64 min, qint64 max);

/**
 * @brief downcast_to_sliderable_position
 * downcast the position to sliderable, this is seconds level
 * @param position the position to convert
 * @return the position that can be direct install to
 * the QSilder
 */
inline qint64 downcast_to_sliderable_position(qint64 position) {
	return position / 1000;
}

/**
 * @brief upcast_to_mseconds
 * upcast the position to mseconds, this is mseconds level
 * @param position the position to convert
 * @return the position that can be direct install to
 * the QSilder
 */
inline qint64 upcast_to_mseconds(qint64 position) {
	return position * 1000;
}

/**
 * @brief toScrollLabelText convert the path to scroll label text
 * @param src_path the source path to convert
 * @return the scroll label text
 * @note this will be used in the scroll label
 */
QString toScrollLabelText(const QString& src_path);

};

#endif // UITOOLS_H
