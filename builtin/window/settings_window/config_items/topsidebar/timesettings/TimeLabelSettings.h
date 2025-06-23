#ifndef TIMELABELSETTINGS_H
#define TIMELABELSETTINGS_H

#include <QWidget>
class QLabel;
namespace Ui {
class TimeLabelSettings;
}
class DesktopMainWindow;
class TimeLabelSettings : public QWidget {
	Q_OBJECT

public:
    explicit TimeLabelSettings(DesktopMainWindow* parent = nullptr);
	~TimeLabelSettings();

private:
    Ui::TimeLabelSettings* ui;
    QLabel* operatingTimeLabel;
    struct SettingsPack {
        QColor fontColor;
        QFont font;
    } settingsPack;
    void process_preview();
    void process_apply();
};

#endif // TIMELABELSETTINGS_H
