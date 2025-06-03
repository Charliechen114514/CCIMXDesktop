#include "FrameProvider.h"
#include "settings/settings_figure.h"
#include <QMutex>
#include <QRandomGenerator>
#include <QTimer>
FrameProvider::FrameProvider(
    const QString& valid_base_path,
    QObject* parent) {
    src_query_locker = new QMutex;

	sources_path << valid_base_path;
	static_load.load(valid_base_path);

	this->update_timer = new QTimer(this);
	update_timer->setInterval(Settings::Figure::FIGURE_FRAME_FLUSH_MS);
	connect(update_timer, &QTimer::timeout, this, &FrameProvider::flush_src_once);
}

FrameProvider::~FrameProvider() {
	delete src_query_locker;
}

void FrameProvider::append_src(const QString& valid_base_path) {
	QMutexLocker<QMutex> lock(src_query_locker);
	sources_path << valid_base_path;
}

void FrameProvider::append_srcs(const QStringList& valid_base_paths) {
	QMutexLocker<QMutex> lock(src_query_locker);
	sources_path << valid_base_paths;
}

void FrameProvider::lock_src(const QString& valid_base_path) {
	QMutexLocker<QMutex> lock(src_query_locker);
	update_timer->stop();
	static_load.load(valid_base_path);
}

void FrameProvider::terminate_flow() {
	QMutexLocker<QMutex> lock(src_query_locker);
	update_timer->stop();
}

void FrameProvider::resume_flow() {
	QMutexLocker<QMutex> lock(src_query_locker);
	update_timer->start();
}

void FrameProvider::manual_shuffle_once() {
	QMutexLocker<QMutex> lock(src_query_locker);
	flow_index = QRandomGenerator::global()->bounded(this->sources_path.size());
	static_load.load(sources_path[flow_index]);
}

QPixmap& FrameProvider::src_pixmap() {
	QMutexLocker<QMutex> lock(src_query_locker);
	return static_load;
}

void FrameProvider::flush_src_once() {
	QMutexLocker<QMutex> loc(src_query_locker);
	flow_index++;
	flow_index %= sources_path.size();
	static_load.load(sources_path[flow_index]);
}
