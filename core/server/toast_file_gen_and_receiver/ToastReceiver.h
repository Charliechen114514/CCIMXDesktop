#ifndef TOASTRECEIVER_H
#define TOASTRECEIVER_H
#include "ToastMetaProtocol.h"
#include <QObject>
class FileMonitor;
class ToastReceiver : public QObject {
	Q_OBJECT
public:
    explicit ToastReceiver(FileMonitor* parent = nullptr);
    std::optional<ToastMetaProtocol> fromExternalJsonString(const QString& json_file) const;
signals:
    void postToast(const ToastMetaProtocol& protocolMeta);
private slots:
    void process_newToast(const QStringList& toasts_metas);

private:
    FileMonitor* monitor;
};

#endif // TOASTRECEIVER_H
