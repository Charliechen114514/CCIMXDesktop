#ifndef SYSTEMSTATEWINDOW_H
#define SYSTEMSTATEWINDOW_H

#include <QMainWindow>
class MemoryInfoFetcher;
class CPUStateFetcher;
class ProcessBroswer;
class CPUUsageChart;
QT_BEGIN_NAMESPACE
namespace Ui {
class SystemStateWindow;
}
QT_END_NAMESPACE

class SystemStateWindow : public QMainWindow {
	Q_OBJECT

public:
	enum PageIndex {
		CPUUsage,
		MemoryInfo,
		ProcessBrowser,
		PageIndexMax
	};

	SystemStateWindow(QWidget* parent = nullptr);
	~SystemStateWindow();
	void switch_index(PageIndex index);

private:
	void setup_charts_and_widgets();
	void setup_connections();
	Ui::SystemStateWindow* ui;
	MemoryInfoFetcher* mem_fetcher { nullptr };
	CPUStateFetcher* cpu_fetcher { nullptr };
	ProcessBroswer* process_fetcher { nullptr };
	CPUUsageChart* cpuchart_widget { nullptr };
};
#endif // SYSTEMSTATEWINDOW_H
