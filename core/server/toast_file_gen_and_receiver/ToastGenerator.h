#ifndef TOASTGENERATOR_H
#define TOASTGENERATOR_H
#include "ToastMetaProtocol.h"
#include <QString>
class ToastGenerator {
public:
    /**
     * @brief generate simple metas into json file
     * @param appName
     * @param messageForDisplay
     * @param summon_folder where to summon
     * @return
     */
    static bool simpleToastMeta(
        const QString& appName,
        const QString& messageForDisplay,
        const QString& summon_folder);

    /**
     * @brief generateToastMeta
     * @param metaInfo
     * @param summon_folder
     * @return
     */
    static bool generateToastMeta(
        ToastMetaProtocol&& metaInfo, // for this is about to be consumed
        const QString& summon_folder);
};

#endif // TOASTGENERATOR_H
