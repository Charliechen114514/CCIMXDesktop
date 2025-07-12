#include "ToastPostServer.h"
#include "core/server/toast_file_gen_and_receiver/ToastProxy.h"
#include "core/server/toast_file_gen_and_receiver/ToastReceiver.h"
#include "library/qt_relative/file_monitor/FileMonitor.h"
#include "ui/desktoptoast.h"
ToastPostServer::ToastPostServer(DesktopToast* toast, const QString& monitoring_path, QObject* parent)
    : DesktopServerBase(parent) {
    toastProxy = std::make_shared<ToastProxy>(toast, this);
    receiver = new ToastReceiver(new FileMonitor(monitoring_path, this));
    connect(receiver, &ToastReceiver::postToast,
            this, [this](const ToastMetaProtocol& protocal) {
                if (enabled) {
                    toastProxy->process_toastMeta(protocal);
                }
            });
}
