#include "ProcessBrowserWidget.h"
#include "ui_ProcessBrowserWidget.h"

ProcessBrowserWidget::ProcessBrowserWidget(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::ProcessBrowserWidget) {
	ui->setupUi(this);
	ui->tableWidget->setColumnCount(8);
	ui->tableWidget->setHorizontalHeaderLabels({ "PID", "PPID", "Name", "Full Path", "Threads",
												 "Memory (KB)", "CPU (%)", "User" });
	ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
	ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
	ui->tableWidget->setAlternatingRowColors(true);
	ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
	ui->tableWidget->setSortingEnabled(true);
}

ProcessBrowserWidget::~ProcessBrowserWidget() {
	delete ui;
}

void ProcessBrowserWidget::handle_process_issues(
	const QList<ProcessBroswer::ProcessInfo>& processes) {
	ui->tableWidget->setRowCount(processes.size());

	for (int row = 0; row < processes.size(); ++row) {
		const ProcessBroswer::ProcessInfo& p = processes[row];

		ui->tableWidget->setItem(row, 0, new QTableWidgetItem(QString::number(p.pid)));
		ui->tableWidget->setItem(row, 1, new QTableWidgetItem(QString::number(p.ppid)));
		ui->tableWidget->setItem(row, 2, new QTableWidgetItem(p.name));
		ui->tableWidget->setItem(row, 3, new QTableWidgetItem(p.fullPath));
		ui->tableWidget->setItem(row, 4, new QTableWidgetItem(QString::number(p.threadCount)));
		ui->tableWidget->setItem(row, 5, new QTableWidgetItem(QString::number(p.memoryUsageKB)));
		ui->tableWidget->setItem(row, 6, new QTableWidgetItem(QString::number(p.cpuPercent, 'f', 2)));
		ui->tableWidget->setItem(row, 7, new QTableWidgetItem(p.userName));
	}

	ui->tableWidget->resizeColumnsToContents();
}
