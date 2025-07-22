#ifndef SLIDESETTINGS_H
#define SLIDESETTINGS_H

class PageSwitchingLimiter;
class DesktopMainWindow;
#include <QWidget>
namespace Ui {
class SlideSettings;
}

class SlideSettings : public QWidget {
	Q_OBJECT

public:
    /**
     * @brief SlideSettings
     * @param parent
     */
    explicit SlideSettings(DesktopMainWindow* parent = nullptr);
	~SlideSettings();

private:
    Ui::SlideSettings* ui;
    DesktopMainWindow* window;
    PageSwitchingLimiter* limitive_controller;
};

#endif // SLIDESETTINGS_H
