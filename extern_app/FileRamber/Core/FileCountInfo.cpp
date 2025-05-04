#include "FileCountInfo.h"
#include "CCIMXFileSystemModel.h"
#include <QDir>
#include <QtConcurrentRun>

FileCountImplWorker::~FileCountImplWorker() {
	for (QFuture<void>& f : results) {
		f.cancel();
		f.waitForFinished();
	}
	results.clear();
}

void FileCountImplWorker::deptach_count_task(const QPersistentModelIndex& index, const QString& path) {
	auto req = QtConcurrent::run([=]() {
		if (QThread::currentThread()->isInterruptionRequested())
			return;
		QDir dir(path);
		int count = dir.entryList(QDir::Files | QDir::NoDotAndDotDot).count();
		emit fileCountFinished(index, count);
	});
	/* enboard the issue */
	results.append(req);
}

FileCountInfo::FileCountInfo(CCIMXFileSystemModel* model, QObject* parent)
    : FileInfoProvider(model)
    , QObject(parent) {
    /* Welp, this is expected to bind */
    worker = new FileCountImplWorker(this);
    connect(worker, &FileCountImplWorker::fileCountFinished,
            this, &FileCountInfo::onHandleWorkFinishJob);
}

std::pair<bool, QVariant> FileCountInfo::data(const QModelIndex& index, int role) {
	if (role != Qt::DisplayRole)
		return { false, {} }; /* not the sessions, quit! */

	QString path = models->filePath(index);
	QFileInfo info(path);

	/* file only no need to count */
	if (!info.isDir())
		return { true, "" };

	QPersistentModelIndex pindex(index);

	/* using the value we cached at previous */
	if (cache.contains(pindex) && cache[pindex] >= 0)
		return { true, QString("%1 files").arg(cache[pindex]) };

	if (!requested.contains(pindex)) {
		requested.insert(pindex);
		worker->deptach_count_task(pindex, path);
	}

	return { true, "counting..." };
}

void FileCountInfo::onHandleWorkFinishJob(QPersistentModelIndex index, int count) {
	cache[index] = count;
	const auto& lists = models->get_providers();
	int col = std::distance(lists.begin(), std::find(lists.begin(), lists.end(), this));
	emit models->dataChanged(index.sibling(index.row(), col), index.sibling(index.row(), col));
}
