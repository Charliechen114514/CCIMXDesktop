#include "globaltimersrc.h"
#include <QDateTime>
GlobalTimerSrc::GlobalTimerSrc(QObject* parent)
    : QObject { parent } {
    timer.setInterval(1000);
    connect(&timer, &QTimer::timeout,
            this, [this](){
                emit updateTime(QTime::currentTime());
            });
    timer.start();
}
