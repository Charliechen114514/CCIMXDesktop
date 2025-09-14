#include "clockeventprocessor.h"
#include <QMessageBox>
#include "alarmynote.h"
ClockEventProcessor::ProcessResult
ConsoleProcessor::
    process_events(std::shared_ptr<AlarmyNote> note) {

	qDebug() << "AlarmyNote hooks: " << note->getSimpleNotes()
	         << " As on time: " << note->getTimer();

	return true;
}

ClockEventProcessor::ProcessResult
DefaultProcessor::
    process_events(std::shared_ptr<AlarmyNote> note) {
	// Simply broadcast a messagebox to solve the sessions
	QMessageBox::information(nullptr, "Clock Alarm Once", note->getSimpleNotes());

	return true; // Always handle the finished sessions
}

bool ClockEventProcessor::getLeave_session() const {
    return leave_session;
}

void ClockEventProcessor::setLeave_session(bool newLeave_session) {
    leave_session = newLeave_session;
}

bool ClockEventProcessor::getEnabled() const {
	return enabled;
}

void ClockEventProcessor::setEnabled(bool newEnabled) {
	enabled = newEnabled;
}

QString ClockEventProcessor::getProcessor_name() const {
	return processor_name;
}

void ClockEventProcessor::setProcessor_name(const QString& newProcessor_name) {
	processor_name = newProcessor_name;
}
