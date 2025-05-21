#ifndef DIRENTSIZECOUNTER_H
#define DIRENTSIZECOUNTER_H

#include "FileInfoProvider.h"
#include <QFuture>
#include <QObject>
/**
 * @brief The DirentSizeWorker class really counts the dirent below size
 * and, this is asyncronous, so, sizeCountFinish signals will brings everytings
 */
class DirentSizeWorker : public QObject {
	Q_OBJECT
public:
	explicit DirentSizeWorker(QObject* object = nullptr) { }
	~DirentSizeWorker();
	/**
	 * @brief functions depatch an asyncronous count issues,
	 * @param index the model index where we start the count
	 * @param path the path to the directory
	 */
	void depatch_sizeCount_task(const QPersistentModelIndex& index, const QString& path);
signals:
	/**
	 * @brief sizeCountFinish signals the finish of the count
	 * @param index the model index where we start the count
	 * @param size the size of the directory
	 */
	void sizeCountFinish(QPersistentModelIndex index, qint64 size);

private:
	QList<QFuture<void>> results; ///< the results of the asyncronous tasks
};

/**
 * @brief The DirentSizeCounter class wrapped the worker and provides
 * non-implement-relative interfaces to the views
 */
class DirentSizeCounter : public QObject, public FileInfoProvider {
	Q_OBJECT
public:
	explicit DirentSizeCounter(CCIMXFileSystemModel* model, QObject* parent = nullptr);
	/**
	 * @brief provide_section_name means everything in the name lol
	 * @return the section name
	 */
	inline QString provide_section_name() {
		return "File Size";
	}

	/**
	 * @brief data provide the data to the views
	 * @param index the model index
	 * @param role the role of the index
	 * @return returns the file size of the index, if the data is not
	 * available, it will return with {false, {}}
	 */
	std::pair<bool, QVariant> data(const QModelIndex& index, int role);
private slots:
	/**
	 * @brief sizeCountFinish's hook
	 * @param index the model index where we start the count
	 * @param size the size of the directory
	 */
	void onHandleWorkFinishJob(QPersistentModelIndex index, qint64 size);

private:
	DirentSizeWorker* worker; ///< worker the kernel to drive fetch the size
	/* Thus I must copy the session... */
	/* Thanks AI, I solved the persis issue */
	/* These are using in caching the already in s */
	mutable QHash<QPersistentModelIndex, qint64> cache; ///< the cached size, for next, we can get the index directly
	mutable QSet<QPersistentModelIndex> requested; ///< the requested index
};

#endif // DIRENTSIZECOUNTER_H
