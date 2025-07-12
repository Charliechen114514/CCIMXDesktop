#ifndef TOASTGENERATOR_H
#define TOASTGENERATOR_H
#include "ToastMetaProtocol.h"
#include <QString>
class ToastGenerator {
public:
    static bool simpleToastMeta(
        const QString& appName,
        const QString& messageForDisplay,
        const QString& summon_folder);

    static bool generateToastMeta(
        ToastMetaProtocol&& metaInfo, // for this is about to be consumed
        const QString& summon_folder);
};

#endif // TOASTGENERATOR_H
