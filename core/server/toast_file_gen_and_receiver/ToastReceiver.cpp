#include "ToastReceiver.h"
#include "library/qt_relative/file_monitor/FileMonitor.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
ToastReceiver::ToastReceiver(FileMonitor* parent)
    : QObject { parent } {
    monitor = parent;
    connect(monitor, &FileMonitor::newFiles,
            this, &ToastReceiver::process_newToast);
}

std::optional<ToastMetaProtocol> ToastReceiver::fromExternalJsonString(const QString& json_file) const {
    return ToastMetaProtocol::from_json_string(json_file);
}

void ToastReceiver::process_newToast(const QStringList& toasts_metas) {
    for (const auto& each_file : toasts_metas) {
        QFile f(each_file);
        if (f.open(QIODevice::ReadOnly)) {
            auto possible_toast = ToastMetaProtocol::from_json_string(f.readAll());
            if (possible_toast.has_value()) {
                emit postToast(possible_toast.value()); // Alright! Broadcast the session
            } else {
                qCritical() << "Error in parsing the file to json: " << each_file;
            }
            f.close();
        } else {
            qCritical() << "Error while processing toast making with"
                           " path "
                        << each_file;
        }
    }
    for (const auto& f : toasts_metas)
        QFile::remove(f);
}
