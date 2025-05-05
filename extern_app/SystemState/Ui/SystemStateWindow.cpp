#include "SystemStateWindow.h"
#include "Core/CPUStateFetcher.h"
#include "Core/MemoryInfoFetcher.h"
#include "Core/ProcessBroswer.h"
#include "Ui/CPUUsageChart.h"
#include "Ui/MemoryUsageChart.h"
#include "Ui/ProcessBrowserWidget.h"
#include "Ui/stackpage_switcher_animation.h"
#include "ui_SystemStateWindow.h"
SystemStateWindow::SystemStateWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::SystemStateWindow) {
	ui->setupUi(this);
	mem_fetcher = new MemoryInfoFetcher(this);
	cpu_fetcher = new CPUStateFetcher(this);
	process_fetcher = new ProcessBroswer(this);
	/* setup the ui first */
	setup_charts_and_widgets();
	setup_connections();
	mem_fetcher->set_capture_state(true);
	cpu_fetcher->set_capture_state(true);
	process_fetcher->set_capture_state(true);
}

SystemStateWindow::~SystemStateWindow() {
	delete ui;
}

void SystemStateWindow::switch_index(PageIndex index) {
	int currentIndex = ui->display_stackwidget->currentIndex();
	if (currentIndex < 0 || currentIndex == index)
		return;

	StackpageSwitcherAnimation::AnimationInfo info;
	info.new_index = static_cast<int>(index);
	info.toLeft = (currentIndex < info.new_index);
	StackpageSwitcherAnimation::process_animations(ui->display_stackwidget, &info);
}

void SystemStateWindow::setup_charts_and_widgets() {
	QList<std::function<void()>> adders;
	adders.reserve(PageIndex::PageIndexMax);
	std::function<void()> cpuchart_adder = [this]() {
		cpuchart_widget = new CPUUsageChart(this);
		ui->display_stackwidget->addWidget(cpuchart_widget);
		connect(cpu_fetcher, &CPUStateFetcher::flush_cpustate,
				cpuchart_widget, &CPUUsageChart::flush_from_cpudriver);
	};
	adders.insert(PageIndex::CPUUsage, cpuchart_adder);
	std::function<void()> memorychart_adder = [this]() {
		auto memchart_widget = new MemoryUsageChart(this);
		ui->display_stackwidget->addWidget(memchart_widget);
		connect(mem_fetcher, &MemoryInfoFetcher::finish_detect_memory,
				memchart_widget, &MemoryUsageChart::flush_ui_once);
	};
	adders.insert(PageIndex::MemoryInfo, memorychart_adder);

	std::function<void()> process_adder = [this]() {
		auto process_widget = new ProcessBrowserWidget(this);
		ui->display_stackwidget->addWidget(process_widget);
		connect(process_fetcher, &ProcessBroswer::fetch_finish,
				process_widget, &ProcessBrowserWidget::handle_process_issues);
	};
	adders.insert(PageIndex::ProcessBrowser, process_adder);
	for (const auto& add_func : adders) {
		add_func();
	}
}

void SystemStateWindow::setup_connections() {
	connect(ui->btn_cpu, &QPushButton::clicked, this, [this]() {
		switch_index(PageIndex::CPUUsage);
	});
	connect(ui->btn_memory, &QPushButton::clicked, this, [this]() {
		switch_index(PageIndex::MemoryInfo);
	});
	connect(ui->btn_process, &QPushButton::clicked, this, [this]() {
		switch_index(PageIndex::ProcessBrowser);
	});
}
