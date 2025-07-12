#include "ToastGenerator.h"
#include <QDir>
#include <QFile>

namespace {
QString fromMetaInfoGenToastFileName(const ToastMetaProtocol& metas) {
    return QStringList { metas.meta_appName, QString::number(metas.announceTime.toSecsSinceEpoch()) }.join('_');
}
}

bool ToastGenerator::simpleToastMeta(
    const QString& appName,
    const QString& messageForDisplay,
    const QString& summon_folder) {
    return generateToastMeta({ appName, messageForDisplay }, summon_folder);
}

bool ToastGenerator::generateToastMeta(
    ToastMetaProtocol&& metaInfo,
    const QString& summon_folder) {
    QString filePath = QDir(summon_folder).filePath(fromMetaInfoGenToastFileName(metaInfo));
    QFile f(filePath);
    if (f.open(QIODevice::WriteOnly)) {
        // open success
        QString jsonString = metaInfo.toString();
        f.write(jsonString.toStdString().data());
        f.close();
    } else {
        // open failed
        qCritical() << "Error in summon toast meta json, these may cause failed"
                       " of some listening server";
        return false;
    }
    return true;
}
