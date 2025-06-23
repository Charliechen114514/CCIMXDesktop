#include "GlobalClockSources.h"
#include <QDateTime>
#include <QTimer>
GlobalClockSources::GlobalClockSources(QObject* parent)
    : QObject { parent } {
    internal_updater = new QTimer(this);

    connect(internal_updater, &QTimer::timeout,
            this, [this]() {
                emit timeUpdate(QTime::currentTime());
            });
    internal_updater->setInterval(SEC_PERIOD);
    internal_updater->start();
}
