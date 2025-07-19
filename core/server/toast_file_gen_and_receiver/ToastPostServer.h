#ifndef TOASTPOSTSERVER_H
#define TOASTPOSTSERVER_H
#include "core/server/DesktopServerBase.h"
#include <memory>
class ToastReceiver;
class DesktopToast;
class ToastProxy;
/**
 * @brief The ToastPostServer class
 * This is a server of toast infomation level
 */
class ToastPostServer : public DesktopServerBase {
    Q_OBJECT
public:
    ToastPostServer(DesktopToast* toast, const QString& monitoring_path, QObject* parent);

private:
    std::shared_ptr<ToastProxy> toastProxy;
    ToastReceiver* receiver;
};

#endif // TOASTPOSTSERVER_H
