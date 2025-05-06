#include "linuxplatformdrivers.h"
#include <QFile>
#include <QString>
#include <QTextStream>
#include <QDir>
#include <pwd.h>
/* Linux Platform Tools here */
/* CPU State
 */
static bool readCPUState(CPUStateFetcher::CPUState &cpu) {
    QFile file("/proc/stat");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;

    QByteArray line = file.readLine();
    file.close();

    if (!line.startsWith("cpu "))
        return false;

    // cpu  122644 127 23062 1073348 2470 0 1023 0 0 0
    //         ↑    ↑    ↑     ↑
    //        us   ni   sy     id
    QStringList parts = QString(line).simplified().split(' ');
    if (parts.size() < 5)
        return false;

    bool ok1, ok2, ok3, ok4, ok5;
    quint64 user = parts[1].toULongLong(&ok1);     // user
    quint64 nice = parts[2].toULongLong(&ok2);     // nice
    quint64 system = parts[3].toULongLong(&ok3);   // system
    quint64 idle = parts[4].toULongLong(&ok4);     // idle
    quint64 iowait = parts[5].toULongLong(&ok5);    // iowait
    if (!(ok1 && ok2 && ok3 && ok4 && ok5))
        return false;

    cpu.user = user + nice;
    cpu.kernel = system;
    cpu.idle = idle + iowait;
    cpu.tol = cpu.user + cpu.kernel + cpu.idle;
    return true;
}




static bool readMemoryStat(MemoryInfoFetcher::MemoryStat &mem_stat) {
    QFile file("/proc/meminfo");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;

    quint64 memTotal = 0;
    quint64 memAvailable = 0;
    quint64 swapTotal = 0;
    quint64 swapFree = 0;

    QTextStream in(&file);
    QString line ;
    while (in.readLineInto(&line)) {
        if (line.startsWith("MemTotal:")) {
            const QStringList parts = line.split(' ', Qt::SkipEmptyParts);
            if (parts.size() > 1)
                memTotal = parts[1].toULongLong() * 1024;
        } else if (line.startsWith("MemAvailable:")) {
            const QStringList parts = line.split(' ', Qt::SkipEmptyParts);
            if (parts.size() > 1)
                memAvailable = parts[1].toULongLong() * 1024;
        } else if (line.startsWith("SwapTotal:")) {
            const QStringList parts = line.split(' ', Qt::SkipEmptyParts);
            if (parts.size() > 1)
                swapTotal = parts[1].toULongLong() * 1024;
        } else if (line.startsWith("SwapFree:")) {
            const QStringList parts = line.split(' ', Qt::SkipEmptyParts);
            if (parts.size() > 1)
                swapFree = parts[1].toULongLong() * 1024;
        }
    }

    file.close();

    if (memTotal == 0)
        return false;

    mem_stat.total_phys_memory = memTotal;
    mem_stat.avail_phys_memory = memAvailable;
    mem_stat.total_virt_memory = memTotal + swapTotal;
    mem_stat.avail_virt_memory = memAvailable + swapFree;

    return true;
}


static void getProcessList(QList<ProcessBroswer::ProcessInfo>& list) {
    QList<ProcessBroswer::ProcessInfo> processList;
    QDir procDir("/proc");
    QStringList pidDirs = procDir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
    for (const QString &entry : pidDirs) {
        bool isNumber;
        int pid = entry.toInt(&isNumber);
        if (!isNumber) continue;

        QString statPath = "/proc/" + entry + "/stat";
        QString cmdlinePath = "/proc/" + entry + "/cmdline";
        QString statusPath = "/proc/" + entry + "/status";
        QString exePath = "/proc/" + entry + "/exe";

        QFile statFile(statPath);
        QFile statusFile(statusPath);
        if (!statFile.open(QIODevice::ReadOnly) || !statusFile.open(QIODevice::ReadOnly))
            continue;

        QTextStream statStream(&statFile);
        QString statLine = statStream.readLine();
        QStringList statParts = statLine.split(' ', Qt::SkipEmptyParts);

        ProcessBroswer::ProcessInfo info;
        info.pid = pid;
        info.ppid = statParts.value(3).toInt();                  // PPID
        info.name = statParts.value(1).remove('(').remove(')'); // Name

        // 获取内存用量、线程数、用户名
        QTextStream statusStream(&statusFile);
        while (!statusStream.atEnd()) {
            QString line = statusStream.readLine();
            if (line.startsWith("VmRSS:")) {
                QStringList parts = line.split(' ', Qt::SkipEmptyParts);
                if (parts.size() >= 2)
                    info.memoryUsageKB = parts[1].toLongLong();
            } else if (line.startsWith("Threads:")) {
                QStringList parts = line.split(' ', Qt::SkipEmptyParts);
                if (parts.size() >= 2)
                    info.threadCount = parts[1].toInt();
            } else if (line.startsWith("Uid:")) {
                QStringList parts = line.split(' ', Qt::SkipEmptyParts);
                if (parts.size() >= 2) {
                    uid_t uid = parts[1].toUInt();
                    struct passwd *pw = getpwuid(uid);
                    info.userName = pw ? QString(pw->pw_name) : "unknown";
                }
            }
        }

        // 获取 full path（可执行路径）
        info.fullPath = QFile::symLinkTarget(exePath);

        // CPU usage：占位为 0.0
        info.cpuPercent = 0.0;

        processList.append(info);
    }

    list = processList;
}




void LinuxPlatformMemoryInfoDriver::factory(MemoryInfoFetcher::MemoryStat &memory_state)
{
    readMemoryStat(memory_state);
}

void LinuxPlatformCPUStateDriver::factory(CPUStateFetcher::CPUState &state)
{
    readCPUState(state);
}

void LinuxPlatformProcessBrowserDriver::factory(QList<ProcessBroswer::ProcessInfo> &lists)
{
    getProcessList(lists);
}
