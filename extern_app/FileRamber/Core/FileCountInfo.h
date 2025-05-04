#ifndef FILECOUNTINFO_H
#define FILECOUNTINFO_H

#include <FileInfoProvider.h>
#include <QFuture>
#include <QObject>
#include <QPersistentModelIndex>
class FileCountImplWorker : public QObject {
	Q_OBJECT
public:
	explicit FileCountImplWorker(QObject* parent = nullptr)
		: QObject(parent) { }
	~FileCountImplWorker();
	void deptach_count_task(const QPersistentModelIndex& index, const QString& path);

signals:
	void fileCountFinished(QPersistentModelIndex index, int count);

private:
	QList<QFuture<void>> results;
};

class FileCountInfo : public QObject, public FileInfoProvider {
	Q_OBJECT
public:
	explicit FileCountInfo(CCIMXFileSystemModel* model, QObject* parent = nullptr);
	inline QString provide_section_name() {
		return "fileCounts";
	}
	std::pair<bool, QVariant> data(const QModelIndex& index, int role);
private slots:
	void onHandleWorkFinishJob(QPersistentModelIndex index, int count);

private:
	FileCountImplWorker* worker;
	/* Thanks AI, I solved the persis issue */
	/* These are using in caching the already in s */
	mutable QHash<QPersistentModelIndex, int> cache;
	mutable QSet<QPersistentModelIndex> requested;
};

#endif // FILECOUNTINFO_H
