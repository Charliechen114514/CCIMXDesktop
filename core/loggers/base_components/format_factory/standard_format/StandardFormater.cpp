#include "StandardFormater.h"
#include <QDateTime>
QString StandardFormater::formativeFactory(QtMsgType type, const QMessageLogContext& context, const QString& msg) {
    QStringList parts;

    if (options_.showTimestamp)
        parts << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");

    parts << from_type(type);

    QString contextInfo;
    if (options_.showFile)
        contextInfo += QString("%1").arg(context.file);
    if (options_.showLine)
        contextInfo += QString(":%1").arg(context.line);
    if (options_.showFunction)
        contextInfo += QString(" %1()").arg(context.function);

    if (!contextInfo.trimmed().isEmpty())
        parts << contextInfo.trimmed();

    parts << msg;

    return QString("[%1]").arg(parts.join("] ["));
}

QString StandardFormater::from_type(QtMsgType type) {
    switch (type) {
    case QtDebugMsg:
        return "Debug";
    case QtWarningMsg:
        return "Warning";
    case QtCriticalMsg:
        return "Critical";
    case QtFatalMsg:
        return "Fatal";
    case QtInfoMsg:
        return "Info";
    }
    return "Unknown Level";
}
