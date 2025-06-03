#include "FlushRequester.h"
#include <QTimer>

FlushRequester::FlushRequester(QObject* parent)
	: QObject { parent } {
	flush_timer = new QTimer(this);
	connect(flush_timer, &QTimer::timeout, this,
			&FlushRequester::flush_once);
}

void FlushRequester::set_flush_status(const bool st)
{
	st ? flush_timer->start() : flush_timer->stop();
}

void FlushRequester::setRequestFlushInterval(const unsigned short interval)
{
	flush_timer->setInterval(interval);
}

unsigned short FlushRequester::getRequestFlushInterval() const
{
	return flush_timer->interval();
}
