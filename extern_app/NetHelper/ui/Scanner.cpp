#include "Scanner.h"
#include "ui_Scanner.h"
#include <QHostAddress>
#include <QMessageBox>
#include <QTcpSocket>
#include <QThread>
#include <QtConcurrent/QtConcurrent>

namespace {
constexpr bool inSegmentSame(quint32 ip) {
    return ip & 0xFFFFFF00;
}
}

Scanner::Scanner(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::Scanner) {
	ui->setupUi(this);
	connect(ui->btn_operate, &QPushButton::clicked, this, [this]() {
		if (stopped) {
			start_scan();
			ui->btn_operate->setText("Abort");
		} else {
			set_stop();
			ui->btn_operate->setText("Scan");
		}
		ui->btn_resume_pause->setEnabled(!stopped);
	});

	connect(ui->btn_resume_pause, &QPushButton::clicked, this, [this]() {
		if (paused) {
			/* set as unpaused */
			set_resume();
			ui->btn_resume_pause->setText("Pause Scan");
		} else {
			set_puase();
			ui->btn_resume_pause->setText("Resume Scan");
		}
	});

	connect(ui->checkBox, &QCheckBox::checkStateChanged, this, &Scanner::refresh_ui_issue);
}

Scanner::~Scanner() {
	set_stop();
	watcher.cancel();
	watcher.waitForFinished();
	delete ui;
}

void Scanner::start_scan() {
	ui->tableWidget->setRowCount(0);
	paused = false;
	stopped = false;

	QHostAddress startAddr(ui->start_ip_edit->text());
	QHostAddress endAddr(ui->end_ip_edit->text());
	qDebug() << "Scan " << ui->start_ip_edit->text() << " <-> " << ui->end_ip_edit->text() << ", port: " << ui->port_spinbox->value();
	quint32 start = startAddr.toIPv4Address();
	quint32 end = endAddr.toIPv4Address();

	if (start == 0 || end == 0) {
		QMessageBox::warning(this, "Info", "IP Format Error! Recheck the start ip format and end ip format!");
		return;
	}

	if (inSegmentSame(start) != inSegmentSame(end)) {
		QMessageBox::warning(this, "Info", "IP provided is not in a segment!");
		return;
	}

	if (start > end) {
		QMessageBox::warning(this, "Info", "start ip should be less then end ip!");
		return;
	}
	allResults.clear();
	quint16 port = ui->port_spinbox->value();
	auto package = InternalScanPack { start, end, port };

	watcher.setFuture(
		QtConcurrent::run(
			&Scanner::process_impl_scan, this, package));
}

void Scanner::set_resume() {
	QMutexLocker locker(&pauseMutex);
	paused = false;
}

void Scanner::set_puase() {
	QMutexLocker locker(&pauseMutex);
	paused = true;
}

void Scanner::set_stop() {
	QMutexLocker locker(&pauseMutex);
	stopped = true;
}

void Scanner::handle_ip_result(const DisplayPackage& pack) {
	allResults << pack;
	refresh_ui_issue();
}

void Scanner::refresh_ui_issue() {
	ui->tableWidget->setRowCount(0);
	bool onlyReachable = ui->checkBox->isChecked();

	for (const auto& entry : std::as_const(allResults)) {
		bool reachable = entry.isAccessible;
		if (onlyReachable && !reachable)
			continue;
		int row = ui->tableWidget->rowCount();
		ui->tableWidget->insertRow(row);
		ui->tableWidget->setItem(row, 0, new QTableWidgetItem(entry.ip));
		ui->tableWidget->setItem(row, 1, new QTableWidgetItem(reachable ? "Reachable" : "UnReachable"));
		ui->tableWidget->setItem(row, 2, new QTableWidgetItem(entry.reason));
	}
}

void Scanner::process_impl_scan(const InternalScanPack pack) {
	for (quint32 ip = pack.start; ip <= pack.end; ++ip) {
		{
			QMutexLocker locker(&pauseMutex);
			if (stopped) {
				return;
			}
			while (paused) {
				locker.unlock();
				QThread::msleep(100);
				locker.relock();
				if (stopped) {
					return;
				}
			}
		}

		QHostAddress addr(ip);
		QString ipStr = addr.toString();
		qDebug() << "holding ipStr" << ipStr;

		QTcpSocket socket;
		socket.connectToHost(ipStr, pack.port);
		bool isReachable = false;
		QString reason;
		if (socket.waitForConnected(TIMEOUT)) {
			socket.disconnectFromHost();
			isReachable = true;
			reason = "Connect Success";
		} else {
			reason = socket.errorString();
		}
		DisplayPackage p = DisplayPackage { isReachable, ipStr, reason };
		/*
		 * invoke this async and enable to communicate cross objects
		 */
		QMetaObject::invokeMethod(
			this, "handle_ip_result",
			Qt::QueuedConnection, Q_ARG(DisplayPackage, p));
	}
}
