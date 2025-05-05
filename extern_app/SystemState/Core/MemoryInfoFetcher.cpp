#include "MemoryInfoFetcher.h"
#include "platforms/PlatformDriverFactory.h"
#include <QDebug>
static constexpr const unsigned long long KB = 1024;
static constexpr const unsigned long long MB = 1024 * KB;
static constexpr const unsigned long long GB = 1024 * MB;

QString MemoryInfoFetcher::format_size(quint64 sizeInBytes) {
	if (sizeInBytes < KB)
		return QString("%1 Bytes").arg(sizeInBytes);
	else if (sizeInBytes < MB)
		return QString::number(sizeInBytes / static_cast<double>(KB), 'f', 2) + " KB";
	else if (sizeInBytes < GB)
		return QString::number(sizeInBytes / static_cast<double>(MB), 'f', 2) + " MB";
	else
		return QString::number(sizeInBytes / static_cast<double>(GB), 'f', 2) + " GB";
}

MemoryInfoFetcher::MemoryInfoFetcher(QObject* parent)
    : QObject { parent } {
    /* setup accordings platform */
    setup_platform_relative();
    flush_timer.setInterval(flush_msecs);
    connect(&flush_timer, &QTimer::timeout, this, &MemoryInfoFetcher::flush_once);
}

MemoryInfoFetcher::~MemoryInfoFetcher() {
	qDebug() << "MemoryInfoFetcher destructor";
	delete platform_driver_base;
	flush_timer.stop();
	qDebug() << "MemoryInfoFetcher destructor done";
}

void MemoryInfoFetcher::set_capture_state(bool st) {
	st ? flush_timer.start() : flush_timer.stop();
}

void MemoryInfoFetcher::flush_once() {
	platform_driver_base->factory(mem_stat);
#ifdef QT_DEBUG
	qDebug() << " Fetch the info once: "
			 << format_size(mem_stat.total_phys_memory) << " "
			 << format_size(mem_stat.avail_phys_memory) << " "
			 << format_size(mem_stat.total_virt_memory) << " "
			 << format_size(mem_stat.avail_virt_memory);
#endif
	emit finish_detect_memory(mem_stat);
}

void MemoryInfoFetcher::setup_platform_relative() {
	qDebug() << "Setup accordings to the platforms for memory sessions";
	this->platform_driver_base = PlatformDriverFactory::meminfo_from_platform();
}
