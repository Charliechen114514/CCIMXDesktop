#include "WallPaperUtilsColliections.h"
#include <QMap>
QStringList WallPaperUtilsColliections::collect_from_qrcs() {
    return {
        ":/backgrounds/bg.png",
        ":/backgrounds/bg2.png"
    };
}

QStringList WallPaperUtilsColliections::prefixs() {
    QStringList prefix;
    for (const auto& each : WallPaperUtilsColliections::PREFIX) {
        prefix << each;
    }
    return prefix;
}
