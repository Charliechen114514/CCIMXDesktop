#include "alarmynotifier.h"
#include "alarmynote.h"
#include <QTimer>
#include <QTime>

AlarmyNotifier::AlarmyNotifier(QObject* parent)
    : QObject { parent } {
    check_timer = new QTimer(this);
    connect(check_timer, &QTimer::timeout, this, &AlarmyNotifier::check_time);

    check_timer->setInterval(1000);
	check_timer->start();
}

void AlarmyNotifier::installAlarmyTime(std::shared_ptr<AlarmyNote> time) {
	qDebug() << "A Timer is install, which will invoke at: " << time->getTimer();
	notes_holdings.emplaceBack(std::move(time));
}

void AlarmyNotifier::removeAlarmyTime(std::shared_ptr<AlarmyNote> time) {
    notes_holdings.removeOne(time);
}

std::shared_ptr<AlarmyNote> AlarmyNotifier::searchWithTime(
    QTime time){
    for (auto& note : notes_holdings) {
        QTime note_time = note->getTimer();
        if (note_time.hour() == time.hour() &&
            note_time.minute() == time.minute() &&
            note_time.second() == time.second()) {
            return note;
        }
    }
    return nullptr;
}

void AlarmyNotifier::check_time(){
    QTime current = QTime::currentTime();
	qDebug() << "Scan Timer session, check time: " << current;
	for (auto& note : notes_holdings) {
		QTime note_time = note->getTimer();
        if (note_time.hour() == current.hour() &&
            note_time.minute() == current.minute() &&
            note_time.second() == current.second()) {
            emit notifyTimeStart(note);
        }
	}
}
