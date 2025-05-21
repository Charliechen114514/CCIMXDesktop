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

/**
 * @brief The SystemStateWindow class
 * The SystemStateWindow class provides the system state window
 */
class SystemStateWindow : public QMainWindow {
	Q_OBJECT

public:
	/**
	 * @brief The PageIndex enum
	 * The PageIndex enum provides the page index
	 * @see switch_index to get to know where to use this
	 */
	enum PageIndex {
		CPUUsage, ///< CPU Usage Index
		MemoryInfo, ///< Memory Info Index
		ProcessBrowser, ///< Process Browser Index
		PageIndexMax ///< Max Page Index Index
	};

	SystemStateWindow(QWidget* parent = nullptr);
	~SystemStateWindow();
	/**
	 * @brief switch_index
	 * @param index
	 * This function is used to switch the page index
	 */
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
