#ifndef CLOCKEVENTBROADCASTER_H
#define CLOCKEVENTBROADCASTER_H

#include <QObject>
class ClockEventProcessor;
class AlarmyNote;
/**
 * @brief The ClockEventBroadcaster class
 */
class ClockEventBroadcaster : public QObject {
	Q_OBJECT
public:
    explicit ClockEventBroadcaster(QObject* parent = nullptr);

	void install_processor(ClockEventProcessor* processor);
	void remove_processor(ClockEventProcessor* processor);

public slots:
    void process_activate_clock(std::shared_ptr<AlarmyNote> note);

private:
	void install_default_action();

private:
	// Processors are here
	QList<ClockEventProcessor*> processors;
};

#endif // CLOCKEVENTBROADCASTER_H
