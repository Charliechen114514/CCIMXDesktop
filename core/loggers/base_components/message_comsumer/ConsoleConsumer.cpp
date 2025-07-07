#include "ConsoleConsumer.h"
#include <system_error>
bool ConsoleConsumer::consume_message(const QString&& message) {
    if (message.isEmpty()) {
        errorStr = "Message is empty";
        return false;
    }

    QByteArray local8BitMsg = message.toLocal8Bit();
    if (local8BitMsg.isEmpty() && !message.isEmpty()) {
        errorStr = "Failed to convert message to local 8-bit encoding";
        return false;
    }

    if (stdout == nullptr) {
        errorStr = "Standard output is not available";
        return false;
    }

    if (fprintf(stdout, "%s\n", local8BitMsg.constData()) < 0) {
        errorStr = "Failed to write message to stdout";
        return false;
    }

    bool result = (fflush(stdout) == 0);
    if (!result) {
        errorStr = QString("Failed to fflush stdout: %1").arg(QString::fromStdString(std::generic_category().message(errno)));
    }

    return result;
}
