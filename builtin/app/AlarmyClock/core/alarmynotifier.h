#ifndef ALARMYNOTIFIER_H
#define ALARMYNOTIFIER_H

#include <QObject>
class AlarmyNote;
class AlarmyNotifier : public QObject {
	Q_OBJECT
public:
    explicit AlarmyNotifier(QObject* parent = nullptr);

    void installAlarmyTime(std::shared_ptr<AlarmyNote> time);
    void removeAlarmyTime(std::shared_ptr<AlarmyNote> time);
    /**
     * @brief searchWithTime search the notifier with clock
     * @param time
     * @return
     */
    std::shared_ptr<AlarmyNote> searchWithTime(QTime time);

signals:
    void notifyTimeStart(std::shared_ptr<AlarmyNote> note);

private slots:
    void check_time();
private:
    QList<std::shared_ptr<AlarmyNote>> notes_holdings;
    QTimer* check_timer;
};

#endif // ALARMYNOTIFIER_H
