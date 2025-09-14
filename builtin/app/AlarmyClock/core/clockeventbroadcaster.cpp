#include "clockeventbroadcaster.h"
#include "clockeventprocessor.h"
#include <QDebug>

ClockEventBroadcaster::ClockEventBroadcaster(QObject* parent)
    : QObject { parent } {
	install_default_action();
}

void ClockEventBroadcaster::install_processor(
    ClockEventProcessor* processor) {
	processors.emplaceBack(processor);
}

void ClockEventBroadcaster::remove_processor(ClockEventProcessor* processor) {
	// remove this processors
	processors.removeOne(processor);
	qDebug() << "Processor is removed!";
}

void ClockEventBroadcaster::process_activate_clock(
    std::shared_ptr<AlarmyNote> note) {

	for (const auto each : std::as_const(processors)) {
		if (each->getEnabled()) {
			// Ok, use the processors install previously
			each->process_events(note);
		}
	}
}

void ClockEventBroadcaster::install_default_action() {
	processors.emplaceBack(new ConsoleProcessor());
	processors.emplaceBack(new DefaultProcessor());
}
