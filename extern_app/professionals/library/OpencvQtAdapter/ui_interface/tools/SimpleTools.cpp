#include "SimpleTools.h"
#include <QFile>
QString SimpleTools::readQss(const QString &filePath)
{
    QFile f(filePath);
    f.open(QIODevice::ReadOnly);
    if(!f.isOpen()){
        throw FailedReadFile(filePath.toStdString());
    }
    return f.readAll();
}
