#include "ToastProxy.h"
#include "ui/desktoptoast.h"

ToastProxy::ToastProxy(DesktopToast* toast, QObject* parent)
    : QObject(parent)
    , toast(toast) {
    if (!toast)
        throw std::invalid_argument("Can not bind a null toast to a proxy");
}

void ToastProxy::process_toastMeta(const ToastMetaProtocol& protocolMeta) {
    const QString metaMessage = protocolMeta.meta_displayMessage;
    toast->set_message(metaMessage);
}
