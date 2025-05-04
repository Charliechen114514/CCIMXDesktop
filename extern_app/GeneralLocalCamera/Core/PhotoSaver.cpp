#include "PhotoSaver.h"
#include <QDateTime>
#include <QFile>
#include <QPixmap>
PhotoSaver::Error PhotoSaver::saveOnce(const QPixmap& image, const QString& dir, const QString prefix) {
	if (image.isNull()) {
		return PhotoSaver::Error::NullImage;
	}

	if (!QFile::exists(dir)) {
		return PhotoSaver::Error::DirUnsavable;
	}
	QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd_HH-mm-ss");
	QString filePath = dir + "/" + timestamp + prefix;

	return image.save(filePath) ? PhotoSaver::Error::SaveSuccess : PhotoSaver::Error::ImageSelfSaveFailed;
}

bool PhotoSaver::dirSavable(const QString& dir) {
	return QFile::exists(dir);
}
