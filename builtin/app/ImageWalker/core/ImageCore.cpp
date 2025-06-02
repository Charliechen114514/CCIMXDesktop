#include "ImageCore.h"
#include <QSet>
namespace {
ImageCore::ErrorType check_accessibility(const QStringList& l, int index) {
	if (index >= l.size())
		return ImageCore::ErrorType::IMAGEREQ_OVERFLOW;
	if (index < 0)
		return ImageCore::ErrorType::IMAGEREQ_UNDERFLOW;
	return ImageCore::ErrorType::NOTHING_THEN;
}
}

void ImageCore::removeImages(const QStringList& what) {
	QMutexLocker<QMutex> locker(&lock);
	paths.erase(std::remove_if(paths.begin(), paths.end(),
							   [whatSet = QSet<QString>(what.cbegin(), what.cend())](const QString& s) {
								   return whatSet.contains(s);
							   }),
				paths.cend());
}

std::optional<QString> ImageCore::peek(const int index) {
	_errorType = check_accessibility(paths, index);
	if (_errorType == ErrorType::NOTHING_THEN) {
		/* request OK */
		return { paths[index] };
	} else {
		return std::nullopt;
	}
}
