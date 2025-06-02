#ifndef IMAGECORE_H
#define IMAGECORE_H
#include <QMutex>
#include <QObject>
/**
 * @brief 	ImageCore indicates the basic image core utils, by providing the
 *			loadable image path
 * 
 */
class ImageCore {
public:
	/**
	 * @brief The ErrorType enum
	 */
	enum class ErrorType {
		NOTHING_THEN, ///< OK
		IMAGEREQ_OVERFLOW, ///< overflow request
		IMAGEREQ_UNDERFLOW ///< underflow request
	};
	/**
	 * @brief ImageCore
	 */
	ImageCore() = default;
	/**
	 * @brief enImages input images
	 * @param l the images
	 */
	inline void enImages(const QStringList& l) {
		QMutexLocker<QMutex> _locker(&lock);
		for (const QString& p : l) {
			if (!paths.contains(p)) {
				paths << p;
			}
		}
	}

	/**
	 * @brief removeImages remove images
	 * @param what
	 */
	void removeImages(const QStringList& what);
	/**
	 * @brief peek get the index to and fetch result
	 * @param index index query index
	 * @return possible path
	 * @note if failed, you need to query the errorType
	 * to see the details
	 */
	std::optional<QString> peek(const int index);
	/**
	 * @brief errorType get the errorType
	 * @return errorType
	 */
	inline ErrorType errorType() const { return _errorType; }
	/**
	 * @brief size get the image size
	 * @return image size
	 */
	inline int size() const { return paths.size(); }
	/**
	 * @brief empty check if empty now
	 * @return is empty?
	 */
	inline bool empty() const { return paths.empty(); }

	/**
	 * @brief clear clears up the holdings
	 * 
	 */
	inline void clear() {
		QMutexLocker<QMutex> _locker(&lock);
		paths.clear();
	}

	/**
	 * @brief fetch the index of holding path
	 * 
	 * @param path 
	 * @return int 
	 */
	inline int index(const QString& path) {
		QMutexLocker<QMutex> _locker(&lock);
		return paths.indexOf(path);
	}

private:
	ErrorType _errorType; ///< internal error
	QMutex lock; ///< helping locker
	QStringList paths; ///< cached paths
};

#endif // IMAGECORE_H
