#ifndef PHOTOSAVER_H
#define PHOTOSAVER_H

#include <QPixmap>
#include <QString>
#include <QtClassHelperMacros>

/**
 * @brief The PhotoSaver class provides static methods for saving images.
 */
class PhotoSaver {
public:
    /**
     * @brief def constructor
     */
    PhotoSaver() = default;

    /**
     * @brief Q_DISABLE_COPY disables copy constructor and assignment operator.
     */
    Q_DISABLE_COPY(PhotoSaver);

    /**
     * @brief Error enum describes possible error states in saving process.
     */
    enum class Error {
        SaveSuccess,       ///< Save was successful
        NullImage,         ///< Image is null
        DirUnsavable,      ///< Directory is not writable or savable
        ImageSelfSaveFailed///< Image saving failed internally
    };

    /**
     * @brief dirSavable checks whether the given directory is writable/savable.
     * @param dir The directory path to check.
     * @return True if directory is writable, otherwise false.
     */
    static bool dirSavable(const QString& dir);

    /**
     * @brief saveOnce saves the image once to the given directory with a filename prefix.
     * @param image The image to save.
     * @param dir The target directory.
     * @param prefix The filename prefix or suffix (default ".jpg").
     * @return The result code of the save operation.
     */
    static Error saveOnce(const QPixmap& image, const QString& dir, const QString prefix = ".jpg");
};

#endif // PHOTOSAVER_H
