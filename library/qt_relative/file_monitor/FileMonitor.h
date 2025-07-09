#ifndef FILEMONITOR_H
#define FILEMONITOR_H
#include <QObject>
#include <QSet>
class QMutex;
class FileMonitor : public QObject {
	Q_OBJECT
    static constexpr const int MONIT_INTV = 2000;

public:
    explicit FileMonitor(const QString& path, QObject* parent = nullptr);
    void setMonitorDirent(const QString& newPath);
    QString monitorDirent() const;
    void setMonitorScanInterval(const int interval);
    int monitorScanInterval() const;

    void setMonitoringState(bool st);
    bool monitoringState() const;

signals:
    void newFiles(const QStringList& files);
    void deletedFiles(const QStringList& files);
    void monitoringChanged(const QString& path);
    void monitoringIntervalChanged(const int new_interval);
    void monitoringStateChanged(const bool new_state);

private slots:
    void processCompareSession();

private:
    QString monitoring_folder;
    QTimer* timer_scan;
    QSet<QString> scanFiles() const;
    QSet<QString> prevFiles;
    std::shared_ptr<QMutex> mutex;
};

#endif // FILEMONITOR_H
