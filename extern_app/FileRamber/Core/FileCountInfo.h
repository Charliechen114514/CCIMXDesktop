#ifndef FILECOUNTINFO_H
#define FILECOUNTINFO_H

#include <FileInfoProvider.h>
#include <QFuture>
#include <QObject>
#include <QPersistentModelIndex>

/**
 * @brief The FileCountImplWorker class makes the file count session
 * actually
 */
class FileCountImplWorker : public QObject {
	Q_OBJECT
public:
	explicit FileCountImplWorker(QObject* parent = nullptr)
		: QObject(parent) { }
	~FileCountImplWorker();
	/**
	 * @brief functions depatch an asyncronous count issues,
	 * @param index the model index where we start the count
	 * @param path the path to the directory
	 */
	void deptach_count_task(const QPersistentModelIndex& index, const QString& path);

signals:
	/**
	 * @brief fileCountFinished signals the finish of the count
	 * @param index the model index where we start the count
	 * @param count the count of the directory
	 */
	void fileCountFinished(QPersistentModelIndex index, int count);

private:
	QList<QFuture<void>> results; ///< the results of the asyncronous tasks
};

class FileCountInfo : public QObject, public FileInfoProvider {
	Q_OBJECT
public:
	explicit FileCountInfo(CCIMXFileSystemModel* model, QObject* parent = nullptr);

	/**
	 * @brief provide_section_name means everything in the name lol
	 * @return the section name
	 */
	inline QString provide_section_name() {
		return "fileCounts";
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
	 * @brief fileCountFinished's hook
	 * @param index the model index where we start the count
	 * @param count the count of the directory
	 */
	void onHandleWorkFinishJob(QPersistentModelIndex index, int count);

private:
	FileCountImplWorker* worker; ///< the worker to do the count
	/* Thanks AI, I solved the persis issue */
	/* These are using in caching the already in s */
	mutable QHash<QPersistentModelIndex, int> cache; ///< the cached size, for next, we can get the index directly
	mutable QSet<QPersistentModelIndex> requested; ///< the requested index
};

#endif // FILECOUNTINFO_H
