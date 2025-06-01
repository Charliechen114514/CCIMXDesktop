#ifndef PINGER_H
#define PINGER_H
#include <QHostAddress>
#include <QWidget>
class QTcpSocket;
class QElapsedTimer;
class QHostInfo;
namespace Ui {
class Pinger;
}

class Pinger : public QWidget {
	Q_OBJECT
	/**
	 * @brief IS_TIMEOUT judge the timeout period length
	 */
	static constexpr const unsigned int IS_TIMEOUT = 1000;
	/**
	 * @brief PING_FREQ_PERIOD pinging frequency max
	 */
	static constexpr const unsigned int PING_FREQ_PERIOD = IS_TIMEOUT;

public:
	/**
	 * @brief Pinger def creator
	 * @param parent
	 */
	explicit Pinger(QWidget* parent = nullptr);
	~Pinger();
private slots:
	void resolveHost(); ///> resolve the possible host
	void on_connected(); /// hooking in ping success
	void on_connectionTimeout(); ///< hooking in ping failed

private:
	Ui::Pinger* ui; ///< ui handle
	QTcpSocket* socket; ///< socket for the test
	QElapsedTimer* elapsed_timer; ///< timer for recording elapse time
	QTimer* pingTimer; ///< ping timer
	QTimer* timeoutTimer; ///< time out judging
	QHostAddress targetAddress; ///< host address middlewares
	bool do_ping { false }; ///< is process ping
	void setup_memory(); ///< setup_memory
	void performPing(); ///< hooking the raw ping
	void abortPing(); ///< quit ping sessions
	void onHostResolved(const QHostInfo& host); ///< handle address solved
};

#endif // PINGER_H
