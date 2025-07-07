#include "DesktopLoggerConvinients.h"
#include <QDebug>
#include <QString>
void Logger::postDebug(const QString& info) {
    qDebug() << info;
}
void Logger::postInfo(const QString& info) {
    qInfo() << info;
}
void Logger::postWarning(const QString& info) {
    qWarning() << info;
}
void Logger::postError(const QString& info) {
    qCritical() << info;
}
void Logger::postFatal(const QString& info) {
    qFatal() << info;
}
