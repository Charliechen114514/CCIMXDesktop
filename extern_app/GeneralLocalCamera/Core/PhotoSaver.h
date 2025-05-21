#ifndef PHOTOSAVER_H
#define PHOTOSAVER_H
#include <QPixmap>
#include <QString>
#include <QtClassHelperMacros>
class PhotoSaver {
public:
	PhotoSaver() = default;
	Q_DISABLE_COPY(PhotoSaver);
	/**
	 * @brief The Error enum provides the situations
	 * and cases of error types
	 */
	enum class Error {
		SaveSuccess, ///< save success
		NullImage, ///< image is null
		DirUnsavable, ///< directory is not savable
		ImageSelfSaveFailed ///< image self save failed
	};

	/**
	 * @brief dirSavable check if the directory is savable
	 * @return true if the directory is savable
	 */
	static bool dirSavable(const QString& dir);

	/**
	 * @brief saveOnce save the image once
	 * @param image the image to save
	 * @param dir the directory to save
	 * @param prefix the prefix of file name
	 * @return the error code
	 */
	static Error saveOnce(const QPixmap& image, const QString& dir, const QString prefix = ".jpg");
};

#endif // PHOTOSAVER_H
