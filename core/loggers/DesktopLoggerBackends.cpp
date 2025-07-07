#include "DesktopLoggerBackends.h"
#include "base_components/format_factory/FormativeFactory.h"
#include "base_components/message_comsumer/LoggerBaseConsumer.h"
#include <QDebug>
#include <QString>
DesktopLoggerBackends::LogStatus DesktopLoggerBackends::processMessage(QtMsgType type, const QMessageLogContext& context, const QString& msg) {
    if (!enabled)
        return LogDisabled;

    return message_consume_backend->consume_message(
               format_factory->formativeFactory(type, context, msg))
        ? LogSuccess
        : LogFailed;
}

DesktopLoggerBackends::DesktopLoggerBackends(std::shared_ptr<FormativeFactory> factory, std::shared_ptr<LoggerBaseConsumer> consumer) {
    hot_install_factory(factory);
    hot_install_consumer(consumer);
}

void DesktopLoggerBackends::hot_install_factory(std::shared_ptr<FormativeFactory> factory) {
    if (!factory) {
        throw std::invalid_argument("Cannot install null formatter factory");
    }

    QMutexLocker<QMutex> locker(&lock);
    format_factory = std::move(factory);
}

void DesktopLoggerBackends::hot_install_consumer(std::shared_ptr<LoggerBaseConsumer> consumer) {
    if (!consumer) {
        throw std::invalid_argument("Cannot install null consumer");
    }

    QMutexLocker<QMutex> locker(&lock);
    message_consume_backend = std::move(consumer);
}
