#ifndef PHOTOSAVER_H
#define PHOTOSAVER_H
#include <QPixmap>
#include <QString>
#include <QtClassHelperMacros>
class PhotoSaver {
public:
	PhotoSaver() = default;
	Q_DISABLE_COPY(PhotoSaver);
	enum class Error {
		SaveSuccess,
		NullImage,
		DirUnsavable,
		ImageSelfSaveFailed
	};
	static bool dirSavable(const QString& dir);
	static Error saveOnce(const QPixmap& image, const QString& dir, const QString prefix = ".jpg");
};

#endif // PHOTOSAVER_H
