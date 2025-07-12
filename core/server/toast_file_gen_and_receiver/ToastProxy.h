#ifndef TOASTPROXY_H
#define TOASTPROXY_H
#include "core/server/toast_file_gen_and_receiver/ToastMetaProtocol.h"
class DesktopToast;
class ToastProxy : public QObject {
public:
    ToastProxy() = delete;
    explicit ToastProxy(DesktopToast* toast, QObject* parent);
public slots:
    void process_toastMeta(const ToastMetaProtocol& protocolMeta);

private:
    DesktopToast* toast;
};

#endif // TOASTPROXY_H
