#include "Pinger.h"
#include "ui_Pinger.h"
#include <QElapsedTimer>
#include <QHostInfo>
#include <QTcpSocket>
#include <QTimer>

Pinger::Pinger(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::Pinger) {
	ui->setupUi(this);
	setup_memory();
	connect(socket, &QTcpSocket::connected, this, &Pinger::on_connected);
	connect(timeoutTimer, &QTimer::timeout, this, &Pinger::on_connectionTimeout);
	connect(pingTimer, &QTimer::timeout, this, &Pinger::resolveHost);
	connect(ui->btn_operate, &QPushButton::clicked, this, [this]() {
		do_ping = !do_ping;
		if (!do_ping) {
			/* isPinging */
			abortPing();
		} else {
			resolveHost();
			pingTimer->start(PING_FREQ_PERIOD);
			ui->btn_operate->setText("Abort");
		}
	});
}

Pinger::~Pinger() {
	delete elapsed_timer;
	delete ui;
}

void Pinger::performPing() {
	quint16 port = ui->port_spinbox->value();
	ui->ping_show->appendPlainText("Pinging...");
	socket->abort();
	elapsed_timer->start();
	socket->connectToHost(targetAddress, port);
	timeoutTimer->start(1000);
}

void Pinger::resolveHost() {
	QString input = ui->ip_port->text();
	if (input.isEmpty()) {
		ui->ping_show->appendPlainText("Submit pingable address");
		abortPing();
		return;
	}

	QHostAddress address;
	if (address.setAddress(input)) {
		targetAddress = address;
		performPing();
	} else {
		QHostInfo::lookupHost(input, this, &Pinger::onHostResolved);
	}
}

void Pinger::onHostResolved(const QHostInfo& host) {
	if (host.error() == QHostInfo::NoError && !host.addresses().isEmpty()) {
		auto list = host.addresses();
		QHostAddress resolvedAddress = list.first();
		targetAddress = resolvedAddress;
		performPing();
	} else {
		ui->ping_show->appendPlainText("Cannot resolved the host name for" + host.hostName());
	}
}

void Pinger::on_connected() {
	timeoutTimer->stop();
	qint64 elapsed = elapsed_timer->elapsed();
	auto format_str = std::format(
		"Address: {}, {} is connected in {} ms!",
		targetAddress.toString().toStdString(),
		socket->peerPort(), elapsed);
	ui->ping_show->appendPlainText(QString::fromStdString(format_str));
	socket->disconnectFromHost();
}

void Pinger::on_connectionTimeout() {
	auto format_str = std::format("Address: {}, {} is unreachable", socket->peerAddress().toString().toStdString(), socket->peerPort());
	socket->abort();
	ui->ping_show->appendPlainText(QString::fromStdString(format_str));
}

void Pinger::abortPing() {
	pingTimer->stop();
	socket->abort();
	do_ping = false;
	ui->btn_operate->setText("Ping");
}

void Pinger::setup_memory() {
	socket = new QTcpSocket(this);
	pingTimer = new QTimer(this);
	timeoutTimer = new QTimer(this);
	elapsed_timer = new QElapsedTimer;
}
