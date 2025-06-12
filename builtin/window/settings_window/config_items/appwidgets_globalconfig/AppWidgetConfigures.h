#ifndef APPWIDGETCONFIGURES_H
#define APPWIDGETCONFIGURES_H

#include "builtin/window/settings_window/cores/SettingsPack.h"
#include <QWidget>
class AppWidget;
namespace Ui {
class AppWidgetConfigures;
}
class DesktopMainWindow;
class AppWidgetConfigures : public QWidget {
	Q_OBJECT

public:
    explicit AppWidgetConfigures(DesktopMainWindow* window, QWidget* parent = nullptr);
	~AppWidgetConfigures();

private slots:
    void process_spinbox_change(int size);

    void on_btn_select_font_clicked();

    void on_btn_select_color_clicked();

    void on_pushButton_clicked();

private:
    Ui::AppWidgetConfigures* ui;
    DesktopMainWindow* window;
    AppWidget* appWidget;
    AppWidgetsSettingsInfoPack info;
};

#endif // APPWIDGETCONFIGURES_H
