#ifndef CLOCKEVENTPROCESSOR_H
#define CLOCKEVENTPROCESSOR_H
#include <QObject>
#include <memory>

class AlarmyNote;
class ClockEventProcessor {
public:
    using ProcessResult = bool;

	ClockEventProcessor() = delete;
	virtual ~ClockEventProcessor() = default;
	ClockEventProcessor(const QString processor)
	    : processor_name(processor) { }
	// force tell the interfaces
	virtual ProcessResult process_events(std::shared_ptr<AlarmyNote> note) = 0;

	bool getLeave_session() const;
	void setLeave_session(bool newLeave_session);

	bool getEnabled() const;
	void setEnabled(bool newEnabled);

	QString getProcessor_name() const;
	void setProcessor_name(const QString& newProcessor_name);

private:
	bool leave_session { false };
	bool enabled { true };

	QString processor_name { "Unamed Processor" };
};

class ConsoleProcessor : public ClockEventProcessor {
public:
	ConsoleProcessor()
	    : ClockEventProcessor("Console Processor") { };
	~ConsoleProcessor() override = default;
	ProcessResult process_events(std::shared_ptr<AlarmyNote> note) override;
};

class DefaultProcessor : public ClockEventProcessor {
public:
	DefaultProcessor()
	    : ClockEventProcessor("Default Processor") { };
	~DefaultProcessor() = default;
	ProcessResult process_events(std::shared_ptr<AlarmyNote> note) override;
};


#endif // CLOCKEVENTPROCESSOR_H
