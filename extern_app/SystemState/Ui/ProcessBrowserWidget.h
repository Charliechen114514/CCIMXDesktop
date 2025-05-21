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
	explicit ProcessBrowserWidget(QWidget* parent = nullptr);
	~ProcessBrowserWidget();

public slots:
	/* Considering the Lists of Processes Then! */
	void handle_process_issues(const QList<ProcessBroswer::ProcessInfo>& infos);

private:
	Ui::ProcessBrowserWidget* ui;
};

#endif // PROCESSBROWSERWIDGET_H
