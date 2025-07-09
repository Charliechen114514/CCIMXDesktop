#include "FileMonitor.h"
#include <QDir>
#include <QMutex>
#include <QTimer>
FileMonitor::FileMonitor(const QString& path, QObject* parent)
    : QObject { parent }
    , monitoring_folder(path) {
    prevFiles = scanFiles();
    mutex = std::make_shared<QMutex>();
    timer_scan = new QTimer(this);
    connect(timer_scan, &QTimer::timeout, this, &FileMonitor::processCompareSession);
    timer_scan->start(MONIT_INTV);
}

void FileMonitor::setMonitorDirent(const QString& newPath) {
    QMutexLocker<QMutex> locker(mutex.get());
    monitoring_folder = newPath;
    emit monitoringChanged(newPath);
}

QString FileMonitor::monitorDirent() const {
    return monitoring_folder;
}

void FileMonitor::setMonitorScanInterval(const int interval) {
    timer_scan->setInterval(interval);
    emit monitoringIntervalChanged(interval);
}

int FileMonitor::monitorScanInterval() const {
    return timer_scan->interval();
}

void FileMonitor::setMonitoringState(bool st) {
    if (st)
        timer_scan->start();
    else
        timer_scan->stop();
    emit monitoringStateChanged(st);
}

bool FileMonitor::monitoringState() const {
    return timer_scan->isActive();
}

void FileMonitor::processCompareSession() {
    QMutexLocker<QMutex> locker(mutex.get());
    QSet<QString> currentFiles = scanFiles();

    QSet<QString> __newFiles = currentFiles - prevFiles;
    if (!__newFiles.isEmpty()) {
        auto files = __newFiles.values();
        qDebug() << "New files are scanned:" << files;
        emit newFiles(files);
    }

    QSet<QString> __deletedFiles = prevFiles - currentFiles;
    if (!__deletedFiles.isEmpty()) {
        auto files = __deletedFiles.values();
        qDebug() << "Deleted files are detected:" << files;
        emit deletedFiles(files);
    }

    prevFiles = currentFiles;
}

QSet<QString> FileMonitor::scanFiles() const {
    QDir dir(monitoring_folder);
    QStringList fileList = dir.entryList(QDir::Files | QDir::NoDotAndDotDot);
    return QSet<QString>(fileList.begin(), fileList.end());
}
