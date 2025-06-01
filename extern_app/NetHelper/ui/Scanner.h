#ifndef SCANNER_H
#define SCANNER_H

#include <QFutureWatcher>
#include <QMutex>
#include <QWidget>

namespace Ui {
class Scanner;
}

class Scanner : public QWidget {
	Q_OBJECT
	static constexpr const unsigned int TIMEOUT = 1500;

public:
	explicit Scanner(QWidget* parent = nullptr);
	~Scanner();
private slots:
	void start_scan();
	void set_resume();
	void set_puase();
	void set_stop();
	void handle_ip_result(bool reachable, QString ip, QString reasonString);

private:
	Ui::Scanner* ui;
	QMutex pauseMutex;
	bool paused { true };
	bool stopped { true };

	struct InternalScanPack {
		quint32 start;
		quint32 end;
		quint16 port;
	};
	void process_impl_scan(const InternalScanPack pack);
	void refresh_ui_issue();
	QFutureWatcher<void> watcher; ///< the watcher holding for the process sessions
	struct DisplayPackage {
		bool isAccessible { false };
		QString ip;
		QString reason;
	};

	QList<DisplayPackage> allResults; ///< result holder
};

#endif // SCANNER_H
