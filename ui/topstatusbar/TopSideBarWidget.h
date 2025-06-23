#ifndef TOPSIDEBARWIDGET_H
#define TOPSIDEBARWIDGET_H

#include <QWidget>
class IconEvent;
class StatusBarIconWidget;
class NetStatusStatusBarIconWidget;
class DesktopMainWindow;
namespace Ui {
class TopSideBarWidget;
}

/**
 * @brief The TopSideBarWidget class
 * holds the top sidebar widgets
 */
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

    /**
     * @brief queryFromName query the status icon bar widgets
     * @param name label name
     * @return if the nullptr, means the widgets is non-exsited
     */
    StatusBarIconWidget* queryFromName(const QString& name);

    /**
     * @brief setHeight set the height for the sessions
     * @param height
     */
    void setHeight(const int height);

    int height_min() const;
    int height_max() const;
    int height() const {
        return selfHeight;
    }

private:
    Ui::TopSideBarWidget* ui;
    void initLeftHandside(); ///< this is using for the create the left hand side
    void initRightHandside(); ///< this is using for the create the right hand side
    int selfHeight; ///< the topSideBarHeight, initing from the desktop settings
    QList<StatusBarIconWidget*> iconsWidgets;
    DesktopMainWindow* mainWindow;
};

#endif // TOPSIDEBARWIDGET_H
