#ifndef TOPSIDEBARWIDGET_H
#define TOPSIDEBARWIDGET_H
#include "desktop_settings.h"
#include <QWidget>
class IconEvent;
class StatusBarIconWidget;
class NetStatusStatusBarIconWidget;
class DesktopMainWindow;
namespace Ui {
class TopSideBarWidget;
}

class TopSideBarWidget : public QWidget {
	Q_OBJECT

public:
    explicit TopSideBarWidget(QWidget* parent = nullptr);
	~TopSideBarWidget();
    void installHookedWindow(DesktopMainWindow* mainWindow);
    /**
     * @brief The AcceptPosition enum
     * tells the accept append positions
     */
    enum class AcceptPosition {
        LeftSide,
        RightSide
    };
    /**
     * @brief append_to_toolside
     * @param src the src positions
     * @param position append the sessions directly
     */
    void append_to_toolside(StatusBarIconWidget* src, AcceptPosition position);

    /**
     * @brief handle_possibleEvent makes it handle the possible events
     * @param events
     */
    void handle_possibleEvent(IconEvent* events);

private:
    Ui::TopSideBarWidget* ui;
    void initLeftHandside(); ///< this is using for the create the left hand side
    void initRightHandside(); ///< this is using for the create the right hand side
    int selfHeight { TOPSIDEBAR_HEIGHT }; ///< the topSideBarHeight, initing from the desktop settings
    QList<StatusBarIconWidget*> iconsWidgets;
    DesktopMainWindow* mainWindow;
};

#endif // TOPSIDEBARWIDGET_H
