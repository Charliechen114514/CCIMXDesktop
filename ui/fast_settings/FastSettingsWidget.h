#ifndef FASTSETTINGSWIDGET_H
#define FASTSETTINGSWIDGET_H
#include <QWidget>

namespace Ui {
class FastSettingsWidget;
}

class QPropertyAnimation;
class BacklightController;
class FastSettingsWidget : public QWidget {
	Q_OBJECT

public:
    explicit FastSettingsWidget(QWidget* parent = nullptr);
    void slideDown();
    void slideUp();
	~FastSettingsWidget();
protected:
    void paintEvent(QPaintEvent* event) override;

private:
    void setup_light_settings();
private:
    std::shared_ptr<BacklightController> backlight_controller;
    Ui::FastSettingsWidget* ui;
};

#endif // FASTSETTINGSWIDGET_H
