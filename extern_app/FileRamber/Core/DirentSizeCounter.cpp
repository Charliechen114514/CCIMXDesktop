#include "DirentSizeCounter.h"
#include "CCIMXFileSystemModel.h"
#include "Core/FileRamberTools.h"
#include <QtConcurrentRun>
namespace {
/* Tools in walking dirent */
static constexpr const int MAX_FILE_ACCEPT = 5;
std::atomic_bool quit_flags { false };

qint64 recursiveSize(const QString& path) {
	if (QThread::currentThread()->isInterruptionRequested()) {
		quit_flags = true;
		return 0;
	}

	if (quit_flags) {
		return 0;
	}
	qint64 size = 0;
	QDir dir(path);
	QFileInfoList entries = dir.entryInfoList(QDir::AllEntries | QDir::NoDotAndDotDot);
	for (const QFileInfo& entry : std::as_const(entries)) {
		if (entry.isDir()) {
			QDir tmp(entry.absoluteFilePath());
			if (tmp.count() > MAX_FILE_ACCEPT) {
				return -1;
			}
			qint64 cnt = recursiveSize(entry.absoluteFilePath());
			if (cnt < 0) {
				return -1;
			}
		} else {
			size += entry.size();
		}
	}
	return size;
}

} /* Tools namespace ends */

DirentSizeCounter::
    DirentSizeCounter(CCIMXFileSystemModel* model, QObject* parent)
    : QObject { parent }
    , FileInfoProvider(model) {

	worker = new DirentSizeWorker(this);
	connect(worker, &DirentSizeWorker::sizeCountFinish,
			this, &DirentSizeCounter::onHandleWorkFinishJob);
}

DirentSizeWorker::~DirentSizeWorker() {
	for (QFuture<void>& f : results) {
		f.cancel();
		f.waitForFinished();
	}
	results.clear();
}

void DirentSizeWorker::
	depatch_sizeCount_task(const QPersistentModelIndex& index, const QString& path) {
	auto req = QtConcurrent::run([=]() {
		if (QThread::currentThread()->isInterruptionRequested())
			return;
		qint64 size = recursiveSize(path);
		emit sizeCountFinish(index, size);
	});
	/* enboard the issue */
	results.append(req);
}

/* we shell on board the result */
void DirentSizeCounter::onHandleWorkFinishJob(
	QPersistentModelIndex index, qint64 size) {
	cache[index] = size;
	const auto& lists = models->get_providers();
	/* get the col of this sessions, meaning the case: the dirent size col should be updated later */
	int col = std::distance(lists.begin(), std::find(lists.begin(), lists.end(), this));

	/* only this one is changed so, it's the same */
	emit models->dataChanged(
		index.sibling(index.row(), col),
		index.sibling(index.row(), col));
}

std::pair<bool, QVariant> DirentSizeCounter::data(const QModelIndex& index, int role) {
	if (role != Qt::DisplayRole)
		return { false, {} }; /* not the sessions, quit! */

	QString path = models->filePath(index);
	QFileInfo info(path);
	if (!info.isDir())
		return { true, FileRamberTools::formatSize(info.size()) };

	QPersistentModelIndex pindex(index);
	if (cache.contains(pindex) && cache[pindex] >= 0)
		return { true, FileRamberTools::formatSize(cache[pindex] / 1024) };

	if (cache.contains(pindex) && cache[pindex] < 0) {
		return { true, "Too Large" };
	}

	if (!requested.contains(pindex)) {
		requested.insert(pindex);
		worker->depatch_sizeCount_task(pindex, path);
	}

	/* session checking is not even stops, so, continues the counting */
	return { true, "counting..." };
}
