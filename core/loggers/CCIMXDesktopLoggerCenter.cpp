#include "CCIMXDesktopLoggerCenter.h"
#include "core/loggers/DesktopLoggerBackends.h"
#include <QMutex>
CCIMXDesktopLoggerCenter::~CCIMXDesktopLoggerCenter() {
}

CCIMXDesktopLoggerCenter& CCIMXDesktopLoggerCenter::global_instance() {
    static CCIMXDesktopLoggerCenter instance; ///< C++11 promised the singlestance of static object
    return instance;
}

void CCIMXDesktopLoggerCenter::registerBackend(DesktopLoggerBackends* backend) {
    if (!backend) {
        throw std::invalid_argument("Cannot register null backend");
    }
    CCIMXDesktopLoggerCenter& inst = CCIMXDesktopLoggerCenter::global_instance();
    QMutexLocker locker(inst.mutex.get());
    auto it = std::find_if(backends.begin(), backends.end(),
                           [backend](const std::shared_ptr<DesktopLoggerBackends>& item) {
                               return item.get() == backend;
                           });

    if (it == backends.end()) {
        if (backend->postSelfStatus()) {
            backends.emplace_back(backend);
        } else {
            qWarning() << "Can not register the backend "
                          "due to the failed of postSelfStatus func";
        }
    }
}

std::vector<std::shared_ptr<DesktopLoggerBackends>> CCIMXDesktopLoggerCenter::backend_shots() const {
    CCIMXDesktopLoggerCenter& inst = CCIMXDesktopLoggerCenter::global_instance();
    QMutexLocker locker(inst.mutex.get());
    return backends;
}

bool CCIMXDesktopLoggerCenter::removeBackend(DesktopLoggerBackends* backend) {

    if (!backend) {
        return false;
    }
    CCIMXDesktopLoggerCenter& inst = CCIMXDesktopLoggerCenter::global_instance();
    QMutexLocker locker(inst.mutex.get());
    auto it = std::find_if(backends.begin(), backends.end(),
                           [backend](const std::shared_ptr<DesktopLoggerBackends>& item) {
                               return item.get() == backend;
                           });

    if (it != backends.end()) {
        backends.erase(it);
        return true;
    }
    return false;
}

void CCIMXDesktopLoggerCenter::availableTargetBackendOnly(DesktopLoggerBackends* backend) {
    for (auto& _backend : backends) {
        _backend->set_enabled(_backend.get() == backend);
    }
}

void CCIMXDesktopLoggerCenter::availableBackends() {
    for (auto& _backend : backends) {
        _backend->set_enabled(true);
    }
}

void CCIMXDesktopLoggerCenter::disableTargetBackends(DesktopLoggerBackends* backend) {
    for (auto& _backend : backends) {
        _backend->set_enabled(_backend.get() != backend);
    }
}

void CCIMXDesktopLoggerCenter::silentBackends() {
    for (auto& _backend : backends) {
        _backend->set_enabled(false);
    }
}

CCIMXDesktopLoggerCenter::CCIMXDesktopLoggerCenter() {
    mutex = std::make_shared<QMutex>();
    old_handler = qInstallMessageHandler(CCIMXDesktopLoggerCenter::globalMessageHandler);
}

void CCIMXDesktopLoggerCenter::
    globalMessageHandler(QtMsgType type,
                         const QMessageLogContext& ctx,
                         const QString& msg) {
    // get the instance first
    CCIMXDesktopLoggerCenter& inst = CCIMXDesktopLoggerCenter::global_instance();

    QMutexLocker locker(inst.mutex.get());

    if (inst.old_handler && inst.broadcast_to_old) {
        // broadcast to old
        inst.old_handler(type, ctx, msg);
    }

    for (const auto& backend : inst.backends) {
        backend->processMessage(type, ctx, msg);
    }
}
