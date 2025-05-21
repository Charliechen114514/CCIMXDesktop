#ifndef DESKTOPTOAST_H
#define DESKTOPTOAST_H
#include <QMutex>
#include <QPointer>
#include <QQueue>
#include <QWidget>
class QLabel;
class QPropertyAnimation;

/**
 * @brief The DesktopToast class is the toast handle classes
 * using less lock messages queue to display the messages upper level
 * requests
 */
class DesktopToast : public QWidget {
    Q_OBJECT
public:
	explicit DesktopToast(QWidget* parent = nullptr);
	/**
	 * @brief set_message push the toast display into the
	 * toast display sessions
	 * @param message
	 * @note this will make a queue like display.
	 * so, if the toast is currently animating, it will not display the new
	 * messages immediately, but wait until the current message is finished
	 */
	void set_message(const QString& message);
signals:
	/**
	 * @brief do_show_toast the signal to show the toast
	 * @param msg waiting display
	 * @note normally, this is just using to simplified the
	 * async model of displaying
	 */
	void do_show_toast(QString msg);

private:
	/**
	 * @brief adjust_place adjust the place of the toast
	 * @note this will be called every time starts
	 */
	void adjust_place();
	/**
	 * @brief start_animation starts the animation
	 */
	void start_animation();
	/**
	 * @brief start_close_animation starts the close animation
	 */
	void start_close_animation();
	/**
	 * @brief set_message_impl makes the real displays
	 * @param message the message to be displayed
	 */
	void set_message_impl(const QString& message);

	QLabel* label; ///< the label to display the message
	QPoint startPos, endPos; ///< recorders
	int animation_maintain_msec { 500 }; ///< the maintain time
	int wait_time { 1000 }; ///< the wait time to standby
	/**
	 * @brief moveAnimation move animation holders
	 * @note
	 * QPointer shell automacially set the pointer
	 * NULL after the object destroyed, else, the session
	 * will be crashed due to Non-vaild objects
	 */
	QPointer<QPropertyAnimation> moveAnimation { nullptr };
	/**
	 * @brief fadeAnimation fade animation holders
	 * @note
	 * QPointer shell automacially set the pointer
	 * NULL after the object destroyed, else, the session
	 * will be crashed due to Non-vaild objects
	 */
	QPointer<QPropertyAnimation> fadeAnimation { nullptr };

	/**
	 * @brief isHandling, marking the animations process
	 * status, is tha animations holdings?
	 */
	QAtomicInteger<bool> isHandling { false };
	/**
	 * @brief pools contains the messages waiting display
	 * @note when large amount of messages smash in,
	 * pools do the job of Buffering the message
	 * warning: Queue itself is not thread safe, add
	 * lock if in multithread, that is the queue_mutex done
	 * @see queue_mutex
	 */
	QQueue<QString> pools;
	QMutex queue_mutex;
};

#endif // DESKTOPTOAST_H
