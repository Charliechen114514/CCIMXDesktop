#ifndef ENVIRONMENTWINDOW_H
#define ENVIRONMENTWINDOW_H
#include "AP3216CAdapterFactory.h"
#include <QMainWindow>
class QTimer;
QT_BEGIN_NAMESPACE
namespace Ui {
class EnvironmentWindow;
}
QT_END_NAMESPACE

class EnvironmentWindow : public QMainWindow {
	Q_OBJECT

public:
	EnvironmentWindow(QWidget* parent = nullptr);
	~EnvironmentWindow();

private:
	Ui::EnvironmentWindow* ui;
	AP3216CAdapterFactory factory;
	QTimer* period_request_timer { nullptr };
	void setup_memory();
	void setup_ui();
	void process_data(const AP3216CData data);
};
#endif // ENVIRONMENTWINDOW_H
