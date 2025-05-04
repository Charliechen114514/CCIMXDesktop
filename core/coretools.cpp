#include "coretools.h"
#include <QDir>

QStringList CoreTools::
enumeratefiles(
const QString &path, const QStringList &nameFilters)
{
    QDir dir(path);

    QFileInfoList fileInfoList = dir.entryInfoList(
        nameFilters,
        QDir::Files | QDir::NoSymLinks | QDir::Readable
        );

    QStringList filePaths;
    for (const QFileInfo& fileInfo : std::as_const(fileInfoList)) {
        filePaths << fileInfo.absoluteFilePath();
    }

    return filePaths;
}


#include <random>
float CoreTools::random_float(const float min, const float max)
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(min, max);
    return dis(gen);
}
