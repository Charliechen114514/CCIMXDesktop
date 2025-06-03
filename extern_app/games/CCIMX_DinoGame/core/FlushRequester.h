#ifndef FLUSHREQUESTER_H
#define FLUSHREQUESTER_H

class QTimer;
#include <QObject>

/**
 * @class FlushRequester
 * @brief Provides timed flush requests using QTimer
 */
class FlushRequester : public QObject {
    Q_OBJECT
public:
	/**
	 * @brief Constructs a FlushRequester object
	 * @param parent Parent QObject
	 */
	explicit FlushRequester(QObject* parent = nullptr);

	/**
	 * @brief Enables or disables flush requests
	 * @param st True to enable flushing, false to disable
	 */
	void set_flush_status(const bool st);

	/**
	 * @brief Sets the flush interval in milliseconds
	 * @param interval Flush interval in ms
	 */
	void setRequestFlushInterval(const unsigned short interval);

	/**
	 * @brief Gets the current flush interval
	 * @return Current flush interval in ms
	 */
	unsigned short getRequestFlushInterval() const;

signals:
	/**
	 * @brief Emitted when a flush is requested
	 */
	void flush_once();

private:
	QTimer* flush_timer; ///< Timer for periodic flush requests
};

#endif // FLUSHREQUESTER_H
