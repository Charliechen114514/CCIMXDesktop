#include "PlainFormarter.h"

QString PlainFormarter::formativeFactory(QtMsgType type, const QMessageLogContext& context, const QString& msg) {
    return msg;
}
