#include "alarmynote.h"

AlarmyNote::AlarmyNote(QTime time, QString simpleNotes)
    :timer(time), simpleNotes(simpleNotes)
{
}

QTime AlarmyNote::getTimer() const {
    return timer;
}

void AlarmyNote::setTimer(const QTime& newTimer) {
    qDebug() << "time has been set to new:" << newTimer;
    timer = newTimer;
}

QString AlarmyNote::getSimpleNotes() const {
    return simpleNotes;
}

void AlarmyNote::setSimpleNotes(const QString& newSimpleNotes) {
    simpleNotes = newSimpleNotes;
}
