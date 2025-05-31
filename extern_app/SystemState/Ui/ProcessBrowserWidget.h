#ifndef PROCESSBROWSERWIDGET_H
#define PROCESSBROWSERWIDGET_H
#include "Core/ProcessBroswer.h"
#include <QWidget>

namespace Ui {
class ProcessBrowserWidget;
}

/**
 * @brief The ProcessBrowserWidget class
 * The ProcessBrowserWidget class provides the process browser widget
 */
class ProcessBrowserWidget : public QWidget {
	Q_OBJECT
	/**
	 * @brief COL_CNT For TableWidgets, this is using how many cols
	 * to display
	 */
	static constexpr const unsigned short COL_CNT = 8;

public:
	/**
	 * @brief Construct a new Process Browser Widget object
	 * 
	 * @param parent 
	 */
	explicit ProcessBrowserWidget(QWidget* parent = nullptr);
	~ProcessBrowserWidget();

public slots:
	/**
	 * @brief handle the process signals for updating
	 * 
	 * @param infos 
	 */
	void handle_process_issues(const QList<ProcessBroswer::ProcessInfo>& infos);

private:
	Ui::ProcessBrowserWidget* ui;
};

#endif // PROCESSBROWSERWIDGET_H
