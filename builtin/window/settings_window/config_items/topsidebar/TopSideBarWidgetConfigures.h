#ifndef TOPSIDEBARWIDGETCONFIGURES_H
#define TOPSIDEBARWIDGETCONFIGURES_H

#include <QWidget>

namespace Ui {
class TopSideBarWidgetConfigures;
}
class TopSideBarWidget;
class DesktopMainWindow;
class TopSideBarWidgetConfigures : public QWidget {
	Q_OBJECT

public:
    explicit TopSideBarWidgetConfigures(DesktopMainWindow* parent = nullptr);
	~TopSideBarWidgetConfigures();

private:
    Ui::TopSideBarWidgetConfigures* ui;
    TopSideBarWidget* toolsidebar;
};

#endif // TOPSIDEBARWIDGETCONFIGURES_H
