#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include <QMainWindow>

namespace Ui {
class SettingsWindow;
}
class DesktopMainWindow;
class ConfigureUiPairs;
/**
 * @brief The SettingsWindow class
 * settings window is here
 */
class SettingsWindow : public QMainWindow {
	Q_OBJECT

public:
    /**
     * @brief SettingsWindow
     * @param parent
     */
    explicit SettingsWindow(DesktopMainWindow* window, QWidget* parent = nullptr);
	~SettingsWindow();

private:
    void setup_connections();
    void setup_panel();
    Ui::SettingsWindow* ui;
    ConfigureUiPairs* pairs;
    DesktopMainWindow* handling_window;
};

#endif // SETTINGSWINDOW_H
