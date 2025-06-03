#ifndef FRAMEPROVIDER_H
#define FRAMEPROVIDER_H

#include <QObject>
#include <QPixmap>
class QMutex;

/**
 * @class FrameProvider
 * @brief Provides and manages frame sources for image processing
 */
class FrameProvider : public QObject {
    Q_OBJECT
public:
	/**
	 * @brief Constructs a FrameProvider with initial path
	 * @param valid_base_path Initial valid source path (required)
	 * @param parent Parent QObject
	 */
	explicit FrameProvider(const QString& valid_base_path, QObject* parent);

	/**
	 * @brief Destructor
	 */
	virtual ~FrameProvider();

	/**
	 * @brief Adds a single source path
	 * @param valid_base_path Valid source path to add
	 */
	void append_src(const QString& valid_base_path);

	/**
	 * @brief Adds multiple source paths
	 * @param valid_base_paths List of valid source paths to add
	 */
	void append_srcs(const QStringList& valid_base_paths);

	/**
	 * @brief Locks to a specific source path
	 * @param valid_base_path Path to lock to
	 */
	void lock_src(const QString& valid_base_path);

	/**
	 * @brief Stops frame updates
	 */
	void terminate_flow();

	/**
	 * @brief Resumes frame updates
	 */
	void resume_flow();

	/**
	 * @brief Manually triggers one frame shuffle
	 */
	void manual_shuffle_once();

	/**
	 * @brief Gets current source pixmap
	 * @return Reference to current QPixmap
	 */
	QPixmap& src_pixmap();

	/**
	 * @brief Pure virtual function to get source bounding rectangle
	 * @return Reference to current QRect
	 */
	virtual QRect& src_bounding_rect() = 0;

private:
	bool locked { false }; ///< Source lock status
	QStringList sources_path; ///< Holds all source paths
	QMutex* src_query_locker; ///< Mutex for thread safety
	QPixmap static_load; ///< Current loaded pixmap
	QTimer* update_timer; ///< Controls update frequency
	short flow_index { 0 }; ///< Current frame index

	/**
	 * @brief Loads and updates current frame once
	 */
	void flush_src_once();
};

#endif // FRAMEPROVIDER_H
