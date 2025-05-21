#ifndef FILERAMBERTOOLS_H
#define FILERAMBERTOOLS_H
#include <QString>
namespace FileRamberTools {

/**
 * @brief formatSize formats the size of the file
 * @param sizeInBytes the size in bytes
 * @return the formatted size
 */
QString formatSize(qint64 sizeInBytes);

}

#endif // FILERAMBERTOOLS_H
