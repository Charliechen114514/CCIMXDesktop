#include "PluginValidator.h"
#include <QString>
bool PluginValidator::isValidPluginFile(const QString& path) {
#ifdef Q_OS_WIN
    return path.endsWith(".dll", Qt::CaseInsensitive);
#elif defined(Q_OS_MAC)
    return path.endsWith(".dylib", Qt::CaseInsensitive);
#else // Assume Linux/Unix
    return path.endsWith(".so", Qt::CaseInsensitive);
#endif
}
