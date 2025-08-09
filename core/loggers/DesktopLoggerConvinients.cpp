#include "DesktopLoggerConvinients.h"
#include <QDebug>
#include <QString>

namespace Logger {

// helper function to format the log message with the name
static inline QString formatLogMessage(const QString& name, const QString& info) {
    if (name.isEmpty()) {
        return info;
    }
    return QStringLiteral("[%1] %2").arg(name, info);
}

// ------------------- Debug logs -------------------

void postDebug(const QString& info) {
    qDebug() << formatLogMessage(QString(), info);
}

void postDebug(const QString& name, const QString& debug_info) {
    qDebug() << formatLogMessage(name, debug_info);
}

void postDebug(const QString& name, QString&& debug_info) {
    qDebug() << formatLogMessage(name, std::move(debug_info));
}

// ------------------- Info logs -------------------

void postInfo(const QString& info) {
    qInfo() << formatLogMessage(QString(), info);
}

void postInfo(const QString& name, const QString& info) {
    qInfo() << formatLogMessage(name, info);
}

void postInfo(const QString& name, QString&& info) {
    qInfo() << formatLogMessage(name, std::move(info));
}

// ------------------- Warning logs -------------------

void postWarning(const QString& info) {
    qWarning() << formatLogMessage(QString(), info);
}

void postWarning(const QString& name, const QString& info) {
    qWarning() << formatLogMessage(name, info);
}

void postWarning(const QString& name, QString&& info) {
    qWarning() << formatLogMessage(name, std::move(info));
}

// ------------------- Error logs -------------------

void postError(const QString& info) {
    qCritical() << formatLogMessage(QString(), info);
}

void postError(const QString& name, const QString& info) {
    qCritical() << formatLogMessage(name, info);
}

void postError(const QString& name, QString&& info) {
    qCritical() << formatLogMessage(name, std::move(info));
}

// ------------------- Fatal logs -------------------

void postFatal(const QString& info) {
    qFatal() << formatLogMessage(QString(), info);
}

void postFatal(const QString& name, const QString& info) {
    qFatal() << formatLogMessage(name, info);
}

void postFatal(const QString& name, QString&& info) {
    qFatal() << formatLogMessage(name, std::move(info));
}

} // namespace Logger
