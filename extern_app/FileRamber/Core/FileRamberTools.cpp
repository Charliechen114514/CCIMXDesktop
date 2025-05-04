#include "FileRamberTools.h"
namespace {
static constexpr const qint64 KB = 1024;
static constexpr const qint64 MB = 1024 * KB;
static constexpr const qint64 GB = 1024 * MB;
}

QString FileRamberTools::formatSize(qint64 sizeInBytes) {
	if (sizeInBytes < KB)
		return QString("%1 Bytes").arg(sizeInBytes);
	else if (sizeInBytes < MB)
		return QString::number(sizeInBytes / static_cast<double>(KB), 'f', 2) + " KB";
	else if (sizeInBytes < GB)
		return QString::number(sizeInBytes / static_cast<double>(MB), 'f', 2) + " MB";
	else
		return QString::number(sizeInBytes / static_cast<double>(GB), 'f', 2) + " GB";
}
