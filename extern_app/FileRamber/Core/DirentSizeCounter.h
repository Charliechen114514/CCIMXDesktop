#ifndef DIRENTSIZECOUNTER_H
#define DIRENTSIZECOUNTER_H

#include "FileInfoProvider.h"
#include <QFuture>
#include <QObject>
class DirentSizeWorker : public QObject {
	Q_OBJECT
public:
	explicit DirentSizeWorker(QObject* object = nullptr) { }
	~DirentSizeWorker();
	void depatch_sizeCount_task(const QPersistentModelIndex& index, const QString& path);
signals:
	void sizeCountFinish(QPersistentModelIndex index, qint64 size);

private:
	QList<QFuture<void>> results;
};

class DirentSizeCounter : public QObject, public FileInfoProvider {
	Q_OBJECT
public:
	explicit DirentSizeCounter(CCIMXFileSystemModel* model, QObject* parent = nullptr);
	inline QString provide_section_name() {
		return "File Size";
	}
	std::pair<bool, QVariant> data(const QModelIndex& index, int role);
private slots:
	void onHandleWorkFinishJob(QPersistentModelIndex index, qint64 size);

private:
	DirentSizeWorker* worker;
	/* Thus I must copy the session... */
	/* Thanks AI, I solved the persis issue */
	/* These are using in caching the already in s */
	mutable QHash<QPersistentModelIndex, qint64> cache;
	mutable QSet<QPersistentModelIndex> requested;
};

#endif // DIRENTSIZECOUNTER_H
