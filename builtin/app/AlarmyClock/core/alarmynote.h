#ifndef ALARMYNOTE_H
#define ALARMYNOTE_H
#include <QTime>
class AlarmyNote {
public:
    AlarmyNote() = delete;
	~AlarmyNote() = default;
	AlarmyNote(QTime time, QString simpleNotes);

    QTime getTimer() const;
    void setTimer(const QTime& newTimer);
    QString getSimpleNotes() const;
    void setSimpleNotes(const QString& newSimpleNotes);

private:
    QTime timer;
    QString simpleNotes;
};

#endif // ALARMYNOTE_H
