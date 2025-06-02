#ifndef SCANNER_H
#define SCANNER_H

#include <QFutureWatcher>
#include <QMutex>
#include <QWidget>

namespace Ui {
class Scanner;
}

/**
 * @brief The Scanner class will scan the port for
 * giving start ip and end ip, and given port
 */
class Scanner : public QWidget {
	Q_OBJECT
	static constexpr const unsigned int TIMEOUT = 1500; ///< how timeout?

public:
	/**
	 * @brief Scanner creater
	 * @param parent
	 */
	explicit Scanner(QWidget* parent = nullptr);
	~Scanner();

private:
	struct DisplayPackage {
		bool isAccessible { false };
		QString ip;
		QString reason;
	};
private slots:
	void start_scan(); ///< scan start
	void set_resume(); ///< resume
	void set_puase(); ///< pause
	void set_stop(); ///< stop

	/**
	 * @brief handle_ip_result hooks of the result
	 * @param is reachable?
	 * @param ip address
	 * @param reasonString the reason why unreachable, or, the success reason of reachable
	 */
	void handle_ip_result(const Scanner::DisplayPackage& pack);

private:
	Ui::Scanner* ui; ///< ui handle
	QMutex pauseMutex; ///< locker for switching status
	bool paused { true }; ///< paused?
	bool stopped { true }; ///< stopped?
	/**
	 * @brief The InternalScanPack class holds the
	 * information scan requires
	 */
	struct InternalScanPack {
		quint32 start; ///< start ip
		quint32 end; ///< end ip
		quint16 port; ///< which port?
	};
	/**
	 * @brief process_impl_scan do the real scan
	 * @param pack the package of the scan requires
	 */
	void process_impl_scan(const InternalScanPack pack);
	/**
	 * @brief refresh_ui_issue hooks the ui update when result come
	 */
	void refresh_ui_issue();
	QFutureWatcher<void> watcher; ///< the watcher holding for the process sessions

	QList<DisplayPackage> allResults; ///< result holder
};

#endif // SCANNER_H
